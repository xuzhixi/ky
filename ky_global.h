//===============================================
/**
 *  @file ky_global.h
 *
 *  @author XuZhiXi
 *  Email   932834199@qq.com or 932834199@163.com
 *
 *  Create datetime:  2012-11-12 17:21:57
 *  Last   modified:  2012-11-12 17:50:58
 *
 *  Description: 
 */
//================================================

#ifndef _KY_GLOBAL_H
#define _KY_GLOBAL_H

#ifdef __GNUC__
#define CHECK_PRINTF_FMT(a,b) __attribute__(( format(printf, a, b) ))
#define CHECK_NORETURN		  __attribute__(( noreturn ))
#define CHECK_CONST			  __attribute__(( const ))
#else
#define CHECK_PRINTF_FMT(a,b)
#define CHECK_NORETURN
#define CHECK_CONST
#endif

#endif // _KY_GLOBAL_H

