#include <stdio.h>
#include <string.h>
#include <sys/epoll.h>

#include <ky_socket.h>
#include <ky_reactor.h>
#include <ky_malloc.h>
#include <ky_cmp.h>

static sint8 ky_cmp_event_t(void *val1, void *val2)
{
	ky_event_t *evt1 = val1;
	ky_event_t *evt2 = val2;

	if ( evt1->event_type > evt2->event_type )
	{
		return 1;
	}
	else if ( evt1->event_type < evt2->event_type )
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

ky_reactor_t *ky_reactor_new(int size, uint32 model)
{
	ky_reactor_t *rat;

	rat = ky_malloc( sizeof(ky_reactor_t) );
	rat->register_skfd_tree = ky_avltree_new(sizeof(int), sizeof(ky_skfd_t), ky_cmp_int);
	rat->delay_del_list = ky_linklist_new(sizeof(ky_reactor_delay_del_t), NULL);
	rat->epfd = epoll_create(size);     // 建立一个epoll,最多可以监听size个fd 
	rat->reactor_model = model;

	return rat;
}

void ky_reactor_release(ky_reactor_t *rat)
{
	ky_avltree_release( rat->register_skfd_tree );
	ky_linklist_release( rat->delay_del_list );
	ky_free( rat );
}

void ky_reactor_add(ky_reactor_t *rat, ky_socket_t *sk, uint32 eventType, ky_reactor_callback_t callback, void *param, size_t paramLen)
{
	ky_event_t event;
	ky_skfd_t *skfdNode;

	// set ky_event_t
	event.event_type = eventType;
	event.callback = callback;                  // 设置回调函数
	event.param = ky_malloc( paramLen );
	memcpy( event.param, param, paramLen );    // 设置回调函数的参数

	skfdNode = ky_avltree_find( rat->register_skfd_tree, &(sk->fd) );
	if ( skfdNode == NULL )
	{
		ky_skfd_t skfd;

		// set ky_skfd_t
		skfd.skfd = sk->fd;
		skfd.evt.data.fd = sk->fd;      // 设置与要处理的事件相关的文件描述符   
		skfd.evt.events = rat->reactor_model | eventType;           // 设置要处理的事件类型
		skfd.register_event_list = ky_linklist_new( sizeof(ky_event_t), ky_cmp_event_t );
		ky_linklist_add( skfd.register_event_list, &event );

		ky_avltree_add(rat->register_skfd_tree, &(sk->fd), &skfd);
		epoll_ctl(rat->epfd, EPOLL_CTL_ADD, sk->fd, &(skfd.evt));     //注册epoll事件
	}
	else
	{
		ky_linklist_add( skfdNode->register_event_list, &event );
		skfdNode->evt.events |= eventType;
		epoll_ctl(rat->epfd, EPOLL_CTL_MOD, sk->fd, &(skfdNode->evt));
	}
}

void ky_reactor_mod(ky_reactor_t *rat, ky_socket_t *sk, uint32 eventType, ky_reactor_callback_t callback, void *param, uint32 paramLen)
{
	ky_skfd_t *skfd;
	ky_event_t event;
	ky_event_t *eventNode;

	skfd = ky_avltree_find( rat->register_skfd_tree, &(sk->fd) );
	if ( skfd == NULL )
	{
		ky_reactor_add( rat, sk, eventType, callback, param, paramLen );
	}
	else
	{
		event.event_type = eventType;
		eventNode = ky_linklist_find( skfd->register_event_list, &event );
		if ( eventNode == NULL )
		{
			ky_reactor_add( rat, sk, eventType, callback, param, paramLen );
		}
		else
		{
			ky_free( eventNode->param );
			eventNode->param = ky_malloc( paramLen );
			memcpy( eventNode->param, param, paramLen );
			eventNode->callback = callback;
		}
	}
}

void ky_reactor_del(ky_reactor_t *rat, ky_socket_t *sk, uint32 eventType)
{
	ky_skfd_t *skfd;
	ky_event_t event;
	ky_event_t *eventNode;

	skfd = ky_avltree_find( rat->register_skfd_tree, &(sk->fd) );
	if ( skfd != NULL )
	{
		event.event_type = eventType;
		eventNode = ky_linklist_find( skfd->register_event_list, &event );
		ky_free( eventNode->param );
		ky_linklist_del( skfd->register_event_list, &event );

		if ( ky_linklist_is_null(skfd->register_event_list) )
		{
			ky_linklist_release( skfd->register_event_list );
			ky_avltree_del( rat->register_skfd_tree, &(sk->fd) );
			epoll_ctl(rat->epfd, EPOLL_CTL_DEL, sk->fd, NULL);  // 删除 sk 的所有epoll事件
		}   
		else
		{
			skfd->evt.events &= (~ eventType);
			epoll_ctl(rat->epfd, EPOLL_CTL_MOD, sk->fd, &(skfd->evt));
		}   
	}
}

void ky_reactor_del_sock(ky_reactor_t *rat, ky_socket_t *sk)
{
	ky_skfd_t *skfd;

	skfd = ky_avltree_find( rat->register_skfd_tree, &(sk->fd) );
	if ( skfd != NULL )
	{
		ky_linklist_release( skfd->register_event_list );
		ky_avltree_del( rat->register_skfd_tree, &(sk->fd) );
		epoll_ctl(rat->epfd, EPOLL_CTL_DEL, sk->fd, NULL);  // 删除 sk 的所有epoll事件
	}   
}

void ky_reactor_del_delay(ky_reactor_t *rat, ky_socket_t *sk, uint32 eventType)
{
	ky_reactor_delay_del_t delayDel;

	delayDel.type = KY_REACTOR_DELAY_EVENT;
	delayDel.sk = sk;
	delayDel.event_type = eventType;
	ky_linklist_add( rat->delay_del_list, &delayDel );
}

void ky_reactor_del_sock_delay(ky_reactor_t *rat, ky_socket_t *sk)
{
	ky_reactor_delay_del_t delayDel;

	delayDel.type = KY_REACTOR_DELAY_SOCK;
	delayDel.sk = sk;
	ky_linklist_add( rat->delay_del_list, &delayDel );
}

void ky_reactor_event_loop(ky_reactor_t *rat)
{   
	int i;
	int eventCount;
	ky_skfd_t *skfd;
	ky_event_t *event;
	ky_linklist_iter_t *iter;
	ky_reactor_delay_del_t *delayDel;

	while(1)
	{
		// 等待有事件发生
		eventCount = epoll_wait(rat->epfd, rat->events, KY_REACTOR_EVERY_HANDLE_COUNT, -1);
		printf("-----------------------------------------------eventCount: %d\n", eventCount);
		for (i=0; i<eventCount; i++)
		{
			// handle event
			skfd = ky_avltree_find( rat->register_skfd_tree, &(rat->events[i].data.fd) );
			iter = ky_linklist_iter( skfd->register_event_list );
			while ( iter != NULL )
			{
				event = ky_linklist_iter_value( iter );
				if ( event->event_type & rat->events[i].events )
				{
					event->callback( rat, event->param );
				}
				iter = ky_linklist_iter_next( iter );
			}

			// delay delete
			iter = ky_linklist_iter( rat->delay_del_list );
			while ( iter != NULL )
			{
				delayDel = ky_linklist_iter_value( iter );
				switch ( delayDel->type )
				{
					case KY_REACTOR_DELAY_EVENT:
						ky_reactor_del(rat, delayDel->sk, delayDel->event_type);
						break;
					case KY_REACTOR_DELAY_SOCK:
						ky_reactor_del_sock(rat, delayDel->sk);
						break;
					default:
						break;
				}
				iter = ky_linklist_iter_next( iter );
			}
			ky_linklist_clear( rat->delay_del_list );
		}
	}
}

