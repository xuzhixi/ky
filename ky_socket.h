#ifndef _KY_SOCKET_H
#define _KY_SOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>

#include <ky_types.h>

/// 表示任意的IP
#define KY_ADDR_ANY "0.0.0.0"
/// 表示任意的端口 
#define KY_PORT_ANY 0
/// 表示阻塞的socket
#define KY_BLOCK 1
/// 表示非阻塞的socket
#define KY_NOBLOCK 0

#ifdef _CPLUSPLUS
extern "C" {
#endif


/// socket结构体
typedef struct ky_socket_t
{
	int fd;		///< 保存socket的句柄
	struct sockaddr_in addr;	///< 保存socket绑定的IP和端口等
}ky_socket_t;

/**
 * @brief 地址结构体
 *
 * 用来表示IP和端口，唯一决定的一个地址
 */
typedef struct ky_address_t
{
	struct sockaddr_in addr;	///< 保存绑定的IP和端口等
}ky_address_t;

/**
 * @brief 初始化一个socket
 *
 * @param  sk		指向要初始化的 socket
 * @param  ip		绑定的IP地址
 * @param  port		绑定的端口
 * @param  type		socket的类型; SOCK_STREAM表示TCP，SOCK_DGRAM表示UDP
 * @param  block	是否是阻塞的socket; KY_BLOCK表示阻塞，KY_NOBLOCK表示非阻塞
 * @retval KY_OK	表示成功
 * @retval KY_ERROR 表示失败
 */
extern sint8 ky_sock_init(ky_socket_t *sk, const char *ip, uint16 port, sint16 type, sint8 block);
/**
 * @brief 监听一个socket
 * 
 * @param  sk			要监听的socket
 * @param  maxWaitCount	允许的最大等待队列(即未accept的socket连接)
 * @retval KY_OK		表示成功
 * @retval KY_ERROR		表示失败
 */
extern sint8 ky_sock_listen(ky_socket_t *sk, int maxWaitCount);
/**
 * @brief 接受一个socket连接
 *
 * @param  clientSk		保存接受的socket
 * @param  block		设置接受的socket阻塞类型; KY_BLOCK表示阻塞，KY_NOBLOCK表示非阻塞
 * @param  serverSk		从serverSk接受一个socket连接
 * @retval KY_OK		表示成功
 * @retval KY_ERROR		表示失败
 */
extern sint8 ky_sock_accept(ky_socket_t *clientSk, sint8 block, ky_socket_t *serverSk);
/**
 * @brief 关闭一个socket
 *
 * @param  sk			要关闭的socket
 * @retval KY_OK		表示成功
 * @retval KY_ERROR		表示失败
 */
extern sint8 ky_sock_close(ky_socket_t *sk);
/**
 * @brief 初始化一个地址结构
 *
 * @param  address		指向要初始化的address结构
 * @param  ip			ip地址
 * @param  port			端口
 */
extern void ky_address_init(ky_address_t *address, const char *ip, uint16 port);
/**
 * @brief 用sk连接到address所指的地址
 *
 * 初始化 sk 时，一般用KY_ADDR_ANY和KY_PORT_ANY就可以了；因为是连接到远程，所以本地的IP和端口是什么也没有关系
 *
 * @param  sk			本地的socket
 * @param  address		要连接的对端地址
 * @retval KY_OK		表示成功
 * @retval KY_ERROR		表示失败
 */
extern sint8 ky_sock_connect(ky_socket_t *sk, ky_address_t *address);

/**
 * @brief 通过TCP发送一个数据包
 *
 * @param  sk			一个已经连接好的TCP socket
 * @param  buf			要发送的数据包地址
 * @param  sendlen		要发送的字节个数
 * @return				成功则返回实际传送出去的字节个数，失败返回-1。错误原因存于errno
 */
extern ssize_t ky_sock_send(ky_socket_t *sk, const char *buf, size_t sendlen);
/**
 * @brief 通过TCP接收一个数据包
 * 
 * @param  sk			一个已经连接好的TCP socket
 * @param  buf			接收数据包的地址
 * @param  buflen		可以接收的最大字节个数
 * @return				成功则返回实际接收的字节个数，失败返回-1。错误原因存在errno
 */
extern ssize_t ky_sock_recv(ky_socket_t *sk, char *buf, size_t buflen);

/**
 * @brief 通过UDP发送一个数据包
 *
 * @param  sk			UDP socket
 * @param  buf			要发送的数据包地址
 * @param  sendlen		要发送的字节个数
 * @param  address		表示发送到的远端地址
 * @return				成功则返回实际传送出去的字节个数，失败返回-1。错误原因存于errno
 */
extern ssize_t ky_sock_sendto(ky_socket_t *sk, const void *buf, size_t sendlen, ky_address_t *address);
/**
 * @brief 通过UDP接收一个数据包
 * 
 * @param  sk			UDP socket
 * @param  buf			接收数据包的地址
 * @param  buflen		可以接收的最大字节个数
 * @param  address		记录发送数据方的地址
 * @return				成功则返回实际接收的字节个数，失败返回-1。错误原因存在errno
 */
extern ssize_t ky_sock_recvfrom(ky_socket_t *sk, void *buf, size_t buflen, ky_address_t *address);

/**
 * @brief 通过socket，获取其绑定的IP
 *
 * @param  sk			socket
 * @param  dst			指向存在IP地址的缓存区(缓存区大小设置为16为佳)
 * @param  dstLen		缓存区的长度
 * @return				IP字符串的地址，实质上是buf的首地址 
 */
extern const char *ky_sock_get_ip(ky_socket_t *sk, char *dst, socklen_t dstLen);
/**
 * @brief 通过socket，获取其绑定的端口 
 * 
 * @param  sk			socket
 * @return				socket绑定的端口
 */
extern uint16 ky_sock_get_port(ky_socket_t *sk);
/**
 * @brief 与ky_sock_get_ip函数一样，不同的是这里通过 address 来获取
 *
 * @see ky_sock_get_ip()
 */
extern const char *ky_address_get_ip(ky_address_t *address, char *dst, socklen_t dstLen);
/**
 * @brief 与ky_sock_get_port函数一样，不同的是这里通过 address 来获取
 *
 * @see ky_sock_get_port()
 */
extern uint16 ky_address_get_port(ky_address_t *address);


#ifdef _CPLUSPLUS
}
#endif

#endif // _KY_SOCKET_H
