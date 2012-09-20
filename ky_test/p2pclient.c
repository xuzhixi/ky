#include <stdio.h>
#include <string.h>

#include <ky_socket.h> 
#include <ky_reactor.h>

void handle_msg(ky_reactor_t *rat, void *param)
{
	ky_socket_t *client;
	ky_address_t addr;
	char ip[16];
	char buf[100];
	int recvLen;

	//发送信息
	//ky_address_init(&addr, "192.168.136.132", 5566);
	//strcpy(buf, "Hello!");
	//ky_sock_sendto(client, buf, strlen(buf), &addr);

	while (1)
	{
		//读取信息
		recvLen = ky_sock_recvfrom(client, buf, sizeof(buf), &addr);
		if ( recvLen != KY_ERROR )
		{
			buf[ recvLen ] = '\0';
			ky_address_get_ip(&addr, ip, sizeof(ip));
			printf("Peer Address %s:%d\n", ip, ky_address_get_port(&addr));
			printf("recv msg is %s\n", buf);
		}
		else
		{
			break;
		}
	}

}

int main(int argc, char *argv[])
{
	ky_socket_t client;
	ky_reactor_t *rat;

	// 创建UDP套接字
	if ( ky_sock_init(&client, KY_ADDR_ANY, KY_PORT_ANY, SOCK_DGRAM, KY_BLOCK) != 0 )
	{
		printf("sock_init error\n");
		return -1;
	}

	rat = ky_reactor_new(1000, KY_REACTOR_ET);  // 初始化反应器 
	ky_reactor_add(rat, &client, EPOLLIN, handle_msg, &client, sizeof(ky_socket_t));    // 注册事件回调
	ky_reactor_event_loop(rat);             // 进入事件循环
	ky_reactor_del_sock(rat, &client);      // 删除server所注册的事件
	// 释放reactor
	ky_reactor_release( rat );

	//关闭socket连接
	ky_sock_close(&client);

	return 0;
}
