#include <stdio.h>
#include <string.h>

#include <ky_socket.h>

int main()
{
	ky_socket_t server;
	ky_address_t addr;
	char ip[16];
	char buf[100];
	int recvLen;
	
	// 创建UDP套接字
	if (ky_sock_init(&server, KY_ADDR_ANY, 5566, SOCK_DGRAM, KY_BLOCK) != 0)
	{
		printf("ky_sock_new error\n");
		return -1;
	}

	while(1)
	{  
		// 接收消息
		recvLen = ky_sock_recvfrom(&server, buf, sizeof(buf), &addr, 0);
		buf[ recvLen ] = '\0';
		ky_address_get_ip(&addr, ip, sizeof(ip)); 
		printf("Peer ky_address_t %s:%d\n", ip, ky_address_get_port(&addr));
		printf("recv msg is %s\n", buf);

		strcpy(buf, "Hello World!");
		// 发送消息
		ky_sock_sendto(&server, buf, strlen(buf), &addr, 0);
	}
	//关闭服务器
	ky_sock_close(&server);

	return 0;
}

