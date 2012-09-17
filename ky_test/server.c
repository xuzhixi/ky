#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h> 

#include <ky_socket.h>
#include <ky_reactor.h>
#include <ky_progress.h>

#define NOTFOUND "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><head><title>kylib</title></head><body>Hello World</body></html>"

void handle_msg(ky_reactor_t *rat, void *param)
{
	ky_socket_t *client = param;	
	char msg[500];
	int recvLen;

	recvLen = ky_sock_recv(client, msg, sizeof(msg));
	while (  recvLen > 0 )
	{
		//读取信息
		msg[ recvLen ] = '\0';
		printf("recv len: %d data: %s\n", recvLen, msg);

		//if ( strcmp( msg, "echo" ) == 0 )
		//{
		//	//发送信息
		//	strcpy(msg, "Hello World!");
		//	ky_sock_send(client, msg, strlen(msg));

		//	//ky_reactor_del(rat, client, EPOLLIN);
		//	//ky_reactor_del_sock_delay(rat, client);
		//}

		recvLen = ky_sock_recv(client, msg, sizeof(msg));
	}
	if ( recvLen == 0 )
	{
		printf("close connect!!!\n");
		ky_sock_close(client);
		ky_reactor_del_sock_delay(rat, client);
	}
	else if ( recvLen < 0 )
	{
		printf("no recv msg! socketID: %d\n", client->fd);
		//发送信息
		//send(client->fd, NOTFOUND, strlen(NOTFOUND), 0);
		//shutdown( client->fd, 2 );
		ky_sock_send(client, NOTFOUND, strlen(NOTFOUND));
		ky_sock_close(client);
		ky_reactor_del_sock_delay(rat, client);
	}
}

void handle_close(ky_reactor_t *rat, void *param)
{
	ky_socket_t *client = param;

	//关闭连接,也可以用close(new_fd);
	//shutdown(new_fd, 2);
	printf("-------------------------------------close connect!!!\n");
	ky_sock_close(client);
}

void handle_connect(ky_reactor_t *rat, void *param)
{
	ky_socket_t *server = param;
	ky_socket_t client;
	char ip[16];

	while (1)
	{
		// 因为使用了epoll的EL模式，所以要循环处理直到等待队列为空
		// (即accept返回-1), epoll的EL模式应该使用no-block的fd
		if (ky_sock_accept(&client, KY_NOBLOCK, server) != 0)
		{
			printf("sock_accept error\n");
			break;
		}
		//打印连接进来主机的ip
		printf("pid: %d connection from %s:%d sockfd: %d\n", getpid(), ky_sock_get_ip(&client, ip, 16), ky_sock_get_port(&client), client.fd);
		
		ky_reactor_add(rat, &client, EPOLLIN, handle_msg, &client, sizeof(ky_socket_t));
		//ky_reactor_add(rat, &client, EPOLLHUP, handle_close, &client, sizeof(ky_socket_t));
	}
}


int main()
{
	ky_socket_t server;
	ky_reactor_t *rat;

	if (ky_sock_init(&server, KY_ADDR_ANY, 8888, SOCK_STREAM, KY_NOBLOCK) != 0)
	{
		printf("sock_init error\n");
		return -1;
	}

	if (ky_sock_listen(&server, 1000) != 0)
	{
		printf("sock_listen error\n");
		return -1;
	}

	printf("bind socketId: %d\n", server.fd);

	KY_PROGRESS_POOL(10, {
		rat = ky_reactor_new(1000, KY_REACTOR_ET);
		
		ky_reactor_add(rat, &server, EPOLLIN, handle_connect, &server, sizeof(ky_socket_t));
		ky_reactor_event_loop(rat);
		ky_reactor_del_sock(rat, &server);
		// 释放reactor
		ky_reactor_release( rat );

		return 0;
	})


	// 关闭服务器
	ky_sock_close(&server);

	return 0;
}

