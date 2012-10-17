//===============================================
/**
 *  @file ky_udt.h
 *
 *  @author XuZhiXi
 *  Email   932834199@qq.com or 932834199@163.com
 *
 *  Create datetime:  2012-10-17 08:15:40
 *  Last   modified:  2012-10-17 08:15:40
 *
 *  Description: 
 */
//================================================

#ifndef _KY_UDT_H
#define _KY_UDT_H

#include "ky_socket.h"
#include "ky_map.h"

#ifdef __cplusplus
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

#ifdef __cplusplus
}
#endif

#endif // _KY_UDP_H
