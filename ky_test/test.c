#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h> 

#include <ky_socket.h>
#include <ky_reactor.h>
#include <ky_progress.h>

#define NOTFOUND "HTTP/1.1 404 Not Found\nContent-Type: text/html\n\n<html><body>request file not found</body></html>"

int main()
{
	ky_socket_t server;
	ky_socket_t client;
	char msg[500];
	int recvLen;
	int sendLen;

	if (ky_sock_init(&server, KY_ADDR_ANY, 5566, SOCK_STREAM, KY_BLOCK) != 0)
	{
		printf("sock_init error\n");
		return -1;
	}

	if (ky_sock_listen(&server, 100) != 0)
	{
		printf("sock_listen error\n");
		return -1;
	}

	while ( 1 )
	{
		if (ky_sock_accept(&client, KY_BLOCK, &server) != 0)
		{
			printf("sock_accept error\n");
			return -1;
		}

		// 接收消息
		printf("socketFd: %d\n", client.fd);
		recvLen = ky_sock_recv(&client, msg, sizeof(msg));
		msg[ recvLen ] = '\0';
		printf("socketFd: %d recv len: %d data: %s\n", client.fd, recvLen, msg);

		// 发送消息
		//sendLen = send( client.fd, NOTFOUND, strlen(NOTFOUND), 0 );
		//printf("socketFd: %d send data len: %d\n", client.fd, sendLen);
		//shutdown( client.fd, 2 );
		sendLen = ky_sock_send(&client, NOTFOUND, strlen(NOTFOUND));
		printf("socketFd: %d send data len: %d\n", client.fd, sendLen);
		ky_sock_close(&client);
	}

	// 关闭服务器
	ky_sock_close(&server);

	return 0;
}

