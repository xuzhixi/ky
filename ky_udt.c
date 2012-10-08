#include <string.h>
#include "ky_udt.h"
#include "ky_log.h"

ssize_t ky_udt_sendto(ky_udt_t *udt, const char *buf, size_t sendLen, ky_address_t *addr)
{
	ssize_t realLen;		// 实际发送的长度

	realLen = ky_sock_sendto( &(udt->sk), buf, sendLen, addr );
	if ( realLen != -1 )
	{
		// 记录到已发送包的Map中,等待响应
	}

	return realLen;
}

ssize_t ky_udt_recvfrom(ky_udt_t *udt, char *buf, size_t bufLen, ky_address_t *addr)
{
	ssize_t recvLen;

	recvLen = ky_sock_recvfrom( &(udt->sk), buf, bufLen, addr );
	if ( recvLen != -1 )
	{
		char ackBuf[20];
		ssize_t realAckLen;	// 实际发送的ACK包长度

		// 判断是否是ACK包，是则把sendMap中的记录删除，然后返回-1; 否则发送一个ACK响应包
		// 发送ACK包
		realAckLen = ky_sock_sendto( &(udt->sk), buf, strlen(ackBuf), addr ); 
		if ( realAckLen == -1 )
		{
			KY_LOG_ERROR("send ack error");
		}
	}

	return recvLen;
}

