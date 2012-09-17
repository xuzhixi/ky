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
typedef char bool;
#endif

typedef char schar;
typedef char sint8;
typedef short int  sint16;
typedef int sint32;
typedef long long sint64;

typedef unsigned char uchar;
typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

#endif // _KY_TYPE_H
