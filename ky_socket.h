#ifndef _KY_SOCKET_H
#define _KY_SOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>

#include <ky_types.h>

#define KY_ADDR_ANY "0.0.0.0"
#define KY_PORT_ANY 0
#define KY_BLOCK 1
#define KY_NOBLOCK 0

#ifdef _CPLUSPLUS
extern "C" {
#endif

typedef struct
{
	int fd;
	struct sockaddr_in addr;
}ky_socket_t;

typedef struct 
{
	struct sockaddr_in addr;
}ky_address_t;


extern sint8 ky_sock_init(ky_socket_t *sk, const char *ip, uint16 port, sint16 type, sint8 block);
extern sint8 ky_sock_listen(ky_socket_t *sk, int maxWaitCount);
extern sint8 ky_sock_accept(ky_socket_t *clientSk, sint8 block, ky_socket_t *serverSk);
extern sint8 ky_sock_close(ky_socket_t *sk);
extern void ky_address_init(ky_address_t *address, const char *ip, uint16 port);
extern sint8 ky_sock_connect(ky_socket_t *sk, ky_address_t *address);

extern ssize_t ky_sock_send(ky_socket_t *sk, const char *buf, size_t sendlen);
extern ssize_t ky_sock_recv(ky_socket_t *sk, char *buf, size_t buflen);

extern const char *ky_sock_get_ip(ky_socket_t *sk, char *dst, socklen_t dstLen);
extern uint16 ky_sock_get_port(ky_socket_t *sk);
extern const char *ky_address_get_ip(ky_address_t *address, char *dst, socklen_t dstLen);
extern uint16 ky_address_get_port(ky_address_t *address);

extern ssize_t ky_sock_recvfrom(ky_socket_t *sk, void *buf, size_t buflen, ky_address_t *address, int flags);
extern ssize_t ky_sock_sendto(ky_socket_t *sk, const void *buf, size_t sendlen, ky_address_t *address, int flags);

#ifdef _CPLUSPLUS
}
#endif

#endif // _KY_SOCKET_H
