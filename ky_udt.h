#ifndef _KY_UDT_H
#define _KY_UDT_H

#include <ky_socket.h>
#include <ky_map.h>

#ifdef _CPLUSPLUS
extern "C" {
#endif

/// 可靠的UDP
typedef struct ky_udt_t
{
	ky_socket_t  sk;			///< socket结构体
	ky_map_t     sendMap;		///< 记录已经发送出去，但是没有收到ACK确认的包
}ky_udt_t;

extern ssize_t ky_udt_sendto(ky_udt_t *udt, const char *buf, size_t sendLen, ky_address_t *addr);
extern ssize_t ky_udt_recvfrom(ky_udt_t *udt, char *buf, size_t bufLen, ky_address_t *addr);

#ifdef _CPLUSPLUS
}
#endif

#endif // _KY_UDP_H
