#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <ky_socket.h> 

int main(int argc, char *argv[])
{
	ky_socket_t client;
	ky_address_t addr;
	char ip[16];
	char buf[100];
	int recvLen;

	//创建流套接字
	if ( ky_sock_init(&client, KY_ADDR_ANY, KY_PORT_ANY, SOCK_STREAM, KY_BLOCK) != 0 )
	{
		printf("sock_init error\n");
		return -1;
	}

	//连接服务器
	ky_address_init(&addr, "192.168.203.160", 5566);
	if ( ky_sock_connect(&client, &addr) == -1 )
	{
		printf("sock_connect error\n");
		return -1;
	}
	printf("My Address %s:%d\n", ky_sock_get_ip(&client, ip, sizeof(ip)), ky_sock_get_port(&client));

	//发送信息
	strcpy(buf, "echo");
	ky_sock_send(&client, buf, strlen(buf));
	printf("already send!!!\n");
	//读取信息
	recvLen = ky_sock_recv(&client, buf, sizeof(buf));
	buf[ recvLen ] = '\0';
	printf("recv msg is %s\n", buf);
	//关闭socket连接
	ky_sock_close(&client);

	return 0;
}
