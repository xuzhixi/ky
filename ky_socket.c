#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include "ky_log.h"
#include "ky_socket.h"

int ky_sock_init(ky_socket_t *sk, const char *ip, unsigned int port, int type, int block)
{
	int optval = 1;
	socklen_t addrLen;

	if  ((sk->fd = socket(AF_INET, type, 0)) == -1) 
	{   
		KY_LOG_ERROR("socket error");
		return -1;
	}   

	setsockopt(sk->fd, SOL_SOCKET, SO_REUSEADDR, (void *)&optval, sizeof(optval));	// SO_REUSEADDR 允许在bind()过程中本地地址可重复使用
	if ( block == KY_NOBLOCK )
	{
		fcntl(sk->fd, F_SETFL, fcntl(sk->fd, F_GETFL) | O_NONBLOCK);
	}

	sk->addr.sin_family = AF_INET;			    // 主机字节顺序
	sk->addr.sin_port = htons(port);			// 把端口转换为网络字节顺序
	sk->addr.sin_addr.s_addr = inet_addr(ip);
	bzero(&(sk->addr.sin_zero), 8);				// 把不需要的位清零

	if(bind(sk->fd, (struct sockaddr *)&(sk->addr), sizeof(struct sockaddr)) == -1)
	{
		KY_LOG_ERROR("bind error");
		return -1;
	}

	if ( port == KY_PORT_ANY )
	{
		addrLen = sizeof(sk->addr);
		// 如果端口为ANY，则获取系统所分配的端口
		getsockname(sk->fd, (struct sockaddr *)&(sk->addr), &addrLen);
	}

	return 0;
}

int ky_sock_listen(ky_socket_t *sk, int maxWaitCount)
{
	//监听进来的socket连接
	if (listen(sk->fd, maxWaitCount) == -1)
	{
		KY_LOG_ERROR("listen error");
		return -1;
	}

	return 0;
}

int ky_sock_accept(ky_socket_t *clientSk, int block, ky_socket_t *serverSk)
{
	socklen_t addrLen;

	addrLen = sizeof(clientSk->addr);
	//阻塞等待进来的连接
	if ((clientSk->fd = accept(serverSk->fd, (struct sockaddr *)&(clientSk->addr), &addrLen)) == -1)
	{
		KY_LOG_ERROR("accept error");
		return -1;
	}

	if ( block == KY_NOBLOCK )
	{
		// 设置为非阻塞
		fcntl(clientSk->fd, F_SETFL, fcntl(clientSk->fd, F_GETFL) | O_NONBLOCK);
	}
	//setsockopt(clifd,SOL_SOCKET,SO_RCVBUF,(const char*)&nRecvBuf,sizeof(int));//设置clifd socket状态,SOL_SOCKET存取socket层, 设置接收缓冲区的大小
	//setsockopt(clifd,SOL_SOCKET,SO_SNDBUF,(const char*)&nSendBuf,sizeof(int));//SORCVBUF设置接收的暂存区大小，SO_SNDBUF设置送出的暂存区大小

	return 0;
}

int ky_sock_close(ky_socket_t *sk)
{
	return close(sk->fd);
}

void ky_address_init(ky_address_t *address, const char *ip, unsigned int port)
{
	address->addr.sin_family = AF_INET;			    //主机字节顺序
	address->addr.sin_port = htons(port);			//把端口转换为网络字节顺序
	address->addr.sin_addr.s_addr = inet_addr(ip);
	bzero(&(address->addr.sin_zero), 8);			//把不需要的位清零
}

int ky_sock_connect(ky_socket_t *sk, ky_address_t *address)
{
	return connect(sk->fd, (struct sockaddr *)&(address->addr), sizeof(address->addr));
}

ssize_t ky_sock_send(ky_socket_t *sk, const char *buf, size_t sendlen)
{
	return send(sk->fd, buf, sendlen, 0);
}

ssize_t ky_sock_recv(ky_socket_t *sk, char *buf, size_t buflen)
{
	return recv(sk->fd, buf, buflen, 0);
}

ssize_t ky_sock_sendto(ky_socket_t *sk, const void *buf, size_t sendlen, ky_address_t *address)
{
	return sendto(sk->fd, buf, sendlen, 0, (struct sockaddr *)&(address->addr), sizeof(address->addr));
}

ssize_t ky_sock_recvfrom(ky_socket_t *sk, void *buf, size_t buflen, ky_address_t *address)
{
	socklen_t addrLen;

	addrLen = sizeof(address->addr);
	return recvfrom(sk->fd, buf, buflen, 0, (struct sockaddr *)&(address->addr), &addrLen);
}

const char *ky_sock_get_ip(ky_socket_t *sk, char *dst, socklen_t dstLen)
{
	return inet_ntop(AF_INET, &(sk->addr.sin_addr), dst, dstLen);
}

unsigned int ky_sock_get_port(ky_socket_t *sk)
{
	return ntohs(sk->addr.sin_port);
}

const char *ky_address_get_ip(ky_address_t *address, char *dst, socklen_t dstLen)
{
	return inet_ntop(AF_INET, &(address->addr.sin_addr), dst, dstLen);
}

unsigned int ky_address_get_port(ky_address_t *address)
{
	return ntohs(address->addr.sin_port);
}

