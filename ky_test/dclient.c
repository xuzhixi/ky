#include <stdio.h>
#include <string.h>

#include <ky_socket.h> 

int main(int argc, char *argv[])
{
	ky_socket_t client;
	ky_address_t addr;
	char ip[16];
	char buf[100];
	int recvLen;

	// 创建UDP套接字
	if ( ky_sock_init(&client, KY_ADDR_ANY, KY_PORT_ANY, SOCK_DGRAM, KY_BLOCK) != 0 )
	{
		printf("sock_init error\n");
		return -1;
	}

	//发送信息
	ky_address_init(&addr, "192.168.203.160", 5566);
	strcpy(buf, "Hello!");
	ky_sock_sendto(&client, buf, strlen(buf), &addr);

	//读取信息
	recvLen = ky_sock_recvfrom(&client, buf, sizeof(buf), &addr);
	buf[ recvLen ] = '\0';
	ky_address_get_ip(&addr, ip, sizeof(ip));
	printf("Peer Address %s:%d\n", ip, ky_address_get_port(&addr));
	printf("recv msg is %s\n", buf);

	//关闭socket连接
	ky_sock_close(&client);

	return 0;
}
