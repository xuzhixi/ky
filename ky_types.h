#ifndef _KY_TYPE_H
#define _KY_TYPE_H

#define KY_TRUE		1
#define KY_FALSE	0

#define KY_OK          0
#define KY_ERROR      -1
#define KY_AGAIN      -2
#define KY_BUSY       -3
#define KY_DONE       -4
#define KY_DECLINED   -5
#define KY_ABORT      -6

#ifndef _CPLUSPLUS
typedef char bool;						///< 布尔型，值为 KY_TRUE 表示真，值为 KY_FALSE 表示假
#endif

typedef char schar;						///< 带符号 字符型
typedef char sint8;						///< 带符号 8位整形
typedef short int  sint16;				///< 带符号 16位整形
typedef int sint32;						///< 带符号 32位整形
typedef long long sint64;				///< 带符号 64位整形

typedef unsigned char uchar;			///< 无符号 字符型
typedef unsigned char uint8;			///< 无符号 8位整形
typedef unsigned short int uint16;		///< 无符号 16位整形
typedef unsigned int uint32;			///< 无符号 32位整形
typedef unsigned long long uint64;		///< 无符号 64位整形

#endif // _KY_TYPE_H
