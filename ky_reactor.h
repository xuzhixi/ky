#ifndef _KY_REACTOR_H
#define _KY_REACTOR_H

#include <ky_types.h>
#include <ky_linklist.h>
#include <ky_avltree.h>

#ifdef _CPLUSPLUS
extern "C" {
#endif

// reactor 每次处理的事件个数
#define KY_REACTOR_EVERY_HANDLE_COUNT 500

#define KY_REACTOR_LT 0
#define KY_REACTOR_ET EPOLLET

typedef enum ky_reactor_delay_t 
{ 
	KY_REACTOR_DELAY_EVENT, 
	KY_REACTOR_DELAY_SOCK
}ky_reactor_delay_t;

typedef struct ky_reactor_delay_del_t
{
	ky_reactor_delay_t type;
	ky_socket_t *sk;
	uint32 event_type;
}ky_reactor_delay_del_t;

typedef struct
{
	int epfd;
	uint32 reactor_model;       // ET model or LT model
	struct epoll_event events[KY_REACTOR_EVERY_HANDLE_COUNT];
	ky_avltree_t *register_skfd_tree;
	ky_linklist_t *delay_del_list;
}ky_reactor_t;

typedef struct
{
	int skfd;
	struct epoll_event evt;
	ky_linklist_t *register_event_list;
}ky_skfd_t;

typedef void (*ky_reactor_callback_t)(ky_reactor_t *, void *);

typedef struct
{
	uint32 event_type;
	ky_reactor_callback_t callback;
	void *param;
}ky_event_t;


extern ky_reactor_t *ky_reactor_new(int size, uint32 model);
extern void ky_reactor_release(ky_reactor_t *rat);
extern void ky_reactor_add(ky_reactor_t *rat, ky_socket_t *sk, uint32 eventType, ky_reactor_callback_t callback, void *param, size_t paramLen);
extern void ky_reactor_mod(ky_reactor_t *rat, ky_socket_t *sk, uint32 eventType, ky_reactor_callback_t callback, void *param, uint32 paramLen);
extern void ky_reactor_del(ky_reactor_t *rat, ky_socket_t *sk, uint32 eventType);
extern void ky_reactor_del_socket(ky_reactor_t *rat, ky_socket_t *sk);
extern void ky_reactor_event_loop(ky_reactor_t *rat);
extern void ky_reactor_del_delay(ky_reactor_t *rat, ky_socket_t *sk, uint32 eventType);
extern void ky_reactor_del_socket_delay(ky_reactor_t *rat, ky_socket_t *sk);

#ifdef _CPLUSPLUS
}
#endif

#endif // _KY_REACTOR_H
