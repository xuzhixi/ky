#ifndef _KY_REACTOR_H
#define _KY_REACTOR_H

#include <sys/epoll.h>
#include "ky_linklist.h"
#include "ky_map.h"

#ifdef __cplusplus
extern "C" {
#endif

/// reactor 每次可以处理的最大事件个数
#define KY_REACTOR_EVERY_HANDLE_COUNT 500

#define KY_REACTOR_LT 0
#define KY_REACTOR_ET EPOLLET

/// 延时删除类型
typedef enum ky_reactor_delay_t 
{ 
	KY_REACTOR_DELAY_EVENT,		///< 只删除某个事件
	KY_REACTOR_DELAY_SOCK		///< 删除socket的所有注册事件
}ky_reactor_delay_t;

/// 延时删除结构体
typedef struct ky_reactor_delay_del_t
{
	ky_reactor_delay_t type;	///< 延时删除类型
	ky_socket_t *sk;
	unsigned int event_type;
}ky_reactor_delay_del_t;

/// 反应器结构体
typedef struct ky_reactor_t
{
	int epfd;							///< epoll的句柄
	unsigned int reactor_model;				///< 反应器的模式: ET模式(KY_REACTOR_ET)、LT模式(KY_REACTOR_LT)
	struct epoll_event events[KY_REACTOR_EVERY_HANDLE_COUNT];		///< 记录已经触发的事件
	ky_map_t *register_skfd_tree;		///< 记录注册的socket事件
	ky_linklist_t *delay_del_list;		///< 延时删除链表
}ky_reactor_t;

/// 记录注册事件的结构体
typedef struct ky_skfd_t
{
	int skfd;							///< 注册事件的socket句柄
	struct epoll_event evt;				///< 记录注册的所有事件
	ky_linklist_t *register_event_list; ///< 记录注册的事件及其回调函数的链表
}ky_skfd_t;

/// 反应器回调函数类型
typedef void (*ky_reactor_callback_t)(ky_reactor_t *, void *);

/// 注册事件结构体
typedef struct ky_event_t
{
	unsigned int event_type;					///< 事件的类型
	ky_reactor_callback_t callback;		///< 回调函数
	void *param;						///< 回调函数的参数
}ky_event_t;


/**
 * @brief new一个反应器 
 *
 * 不再使用的时候，要调用 ky_reactor_release 来释放占用的内存
 *
 * @param  size		可以处理的socket个数
 * @param  model	反应器的模式，ET or LT
 * @return			新建的反应器
 */
extern ky_reactor_t *ky_reactor_new(int size, unsigned int model);
/**
 * @brief 释放一个反应器
 */
extern void ky_reactor_release(ky_reactor_t *rat);
/**
 * @brief 在反应器中注册一个事件
 *
 * @param  rat
 * @param  sk			要注册事件的socket
 * @param  eventType	注册的事件类型(查考epoll的事件类型)
 * @param  callback		回调函数
 * @param  param		回调函数的参数
 * @param  paramLen		回调函数参数的长度
 */
extern void ky_reactor_add(ky_reactor_t *rat, ky_socket_t *sk, unsigned int eventType, ky_reactor_callback_t callback, void *param, size_t paramLen);
/**
 * @brief 在反应器为socket修改一个事件的回调函数和参数
 *
 * 如果没有找到要修改的事件，则为socket注册这个事件
 * 注意不要再回调函数中，调用ky_reactor_mod修改本socket本事件的回调函数(因为该函数正在调用中，修改将会导致不可以预知的错误发生)
 *
 * @param  rat
 * @param  sk			要修改事件的socket
 * @param  eventType	要修改的事件类型(查考epoll的事件类型)
 * @param  callback		回调函数
 * @param  param		回调函数的参数
 * @param  paramLen		回调函数参数的长度
 */
extern void ky_reactor_mod(ky_reactor_t *rat, ky_socket_t *sk, unsigned int eventType, ky_reactor_callback_t callback, void *param, size_t paramLen);
/**
 * @brief 在反应器为socket删除一个注册的事件
 *
 * @param  rat
 * @param  sk
 * @param  eventType	要删除的事件类型
 */
extern void ky_reactor_del(ky_reactor_t *rat, ky_socket_t *sk, unsigned int eventType);
/**
 * @brief 在反应器中删除某个socket注册的所有事件
 */
extern void ky_reactor_del_socket(ky_reactor_t *rat, ky_socket_t *sk);
/**
 * @brief 进入反应器的事件循环
 */
extern void ky_reactor_event_loop(ky_reactor_t *rat);
/**
 * @brief 延时删除反应器中，某个socket的某个注册事件
 *
 * 如果想在socket的A事件的回调函数中，把这个socket的A事件删除掉，只能调用该函数来删除
 * 如果想在socket的A事件回调函数中，删除这个socket的非A事件，可以调用该函数或者调用 ky_reactor_del 函数也可以
 */
extern void ky_reactor_del_delay(ky_reactor_t *rat, ky_socket_t *sk, unsigned int eventType);
/**
 * @brief 延时删除反应器中，某个socket所有注册的事件
 *
 * 在socket的回调函数中，删除这个socket所有注册的事件，只能调用该函数来删除
 * 在socket的回调函数中，如果要删除非本socket所有注册的事件，可以调用该函数或者调用 ky_reactor_del_socket 函数也可以
 */
extern void ky_reactor_del_socket_delay(ky_reactor_t *rat, ky_socket_t *sk);

#ifdef __cplusplus
}
#endif

#endif // _KY_REACTOR_H
