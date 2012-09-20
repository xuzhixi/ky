#include <stdio.h>
#include <string.h>

#include <ky_socket.h>
#include <ky_reactor.h>
#include <ky_log.h>

void handle_msg(ky_reactor_t *rat, void *param)
{
	ky_socket_t *server = param;
	char buf[100];
	int recvLen;
	ky_address_t addr;
	char ip[16];

	while(1)
	{  
		// 接收消息
		recvLen = ky_sock_recvfrom(server, buf, sizeof(buf), &addr);
		if ( recvLen != KY_ERROR )
		{
			buf[ recvLen ] = '\0';

			ky_address_get_ip(&addr, ip, sizeof(ip)); 
			printf("Peer ky_address_t %s:%d\n", ip, ky_address_get_port(&addr));
			printf("recv msg is %s\n", buf);

			strcpy(buf, "Hello World!");
			// 发送消息
			ky_sock_sendto(server, buf, strlen(buf), &addr);
		}
		else
		{
			break;
		}
	}
}

int main()
{
	ky_reactor_t *rat;
	ky_socket_t server;
	
	// 创建UDP套接字
	if (ky_sock_init(&server, KY_ADDR_ANY, 5566, SOCK_DGRAM, KY_BLOCK) != 0)
	{
		KY_LOG_STD_ERROR("ky_sock_new error\n");
		return -1;
	}

	rat = ky_reactor_new(1000, KY_REACTOR_ET);	// 初始化反应器 
	ky_reactor_add(rat, &server, EPOLLIN, handle_msg, &server, sizeof(ky_socket_t));	// 注册事件回调
	ky_reactor_event_loop(rat);				// 进入事件循环
	ky_reactor_del_sock(rat, &server);		// 删除server所注册的事件
	// 释放reactor
	ky_reactor_release( rat );

	// 关闭服务器
	ky_sock_close(&server);

	return 0;
}

