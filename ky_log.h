//===============================================
/**
 *  @file ky_log.h
 *
 *  @author XuZhiXi
 *  Email   932834199@qq.com or 932834199@163.com
 *
 *  Create datetime:  2012-10-17 08:11:48
 *  Last   modified:  2012-10-17 08:11:48
 *
 *  Description: 
 */
//================================================

#ifndef _KY_LOG_H
#define _KY_LOG_H

#include <stdio.h>

#ifdef __linux
#include <pthread.h>
#endif

#define KY_LOG_FILENAME_MAXSIZE 150
#define KY_LOG_MSG_MAXSIZE 256

#define ky_log_debug(log, format, ...) ky_log_msg(log, KY_LOG_LEVEL_DEBUG, __FILE__, __LINE__, format, ##__VA_ARGS__) 
#define ky_log_info(log, format, ...)  ky_log_msg(log, KY_LOG_LEVEL_INFO,  __FILE__, __LINE__, format, ##__VA_ARGS__)
#define ky_log_warn(log, format, ...)  ky_log_msg(log, KY_LOG_LEVEL_WARN,  __FILE__, __LINE__, format, ##__VA_ARGS__)
#define ky_log_error(log, format, ...) ky_log_msg(log, KY_LOG_LEVEL_ERROR, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define ky_log_fatal(log, format, ...) ky_log_msg(log, KY_LOG_LEVEL_FATAL, __FILE__, __LINE__, format, ##__VA_ARGS__)

#define ky_log_open_default(logFile, openMode, level, splitType, splitSize) g_ky_log_default=ky_log_open(logFile, openMode, level, splitType, splitSize)
#define KY_LOG_DEBUG(format, ...) ky_log_msg(g_ky_log_default, KY_LOG_LEVEL_DEBUG, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define KY_LOG_INFO(format, ...)  ky_log_msg(g_ky_log_default, KY_LOG_LEVEL_INFO,  __FILE__, __LINE__, format, ##__VA_ARGS__)
#define KY_LOG_WARN(format, ...)  ky_log_msg(g_ky_log_default, KY_LOG_LEVEL_WARN,  __FILE__, __LINE__, format, ##__VA_ARGS__)
#define KY_LOG_ERROR(format, ...) ky_log_msg(g_ky_log_default, KY_LOG_LEVEL_ERROR, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define KY_LOG_FATAL(format, ...) ky_log_msg(g_ky_log_default, KY_LOG_LEVEL_FATAL, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define ky_log_close_default()	  ky_log_close(g_ky_log_default);g_ky_log_default=NULL

#ifdef __cplusplus
extern "C" {
#endif


/// 日志的等级
typedef enum ky_log_level_t
{
	KY_LOG_LEVEL_OFF,
	KY_LOG_LEVEL_FATAL,
	KY_LOG_LEVEL_ERROR,
	KY_LOG_LEVEL_WARN,
	KY_LOG_LEVEL_INFO,
	KY_LOG_LEVEL_DEBUG,
	KY_LOG_LEVEL_ALL
}ky_log_level_t;

/// 日志结构体
typedef struct ky_log_t
{
	FILE *fd;	
	char *file_name;
	int   split_type;			///< 切割日志的方式: 0 表示不切割; 1 表示按日期切割; 2 表示按大小切割
	int   day;					///< 记录今天是这个月的多少号
	long  split_size;			///< 超过这个大小(字节)会切割日志
#ifdef __linux
	pthread_mutex_t mutex;		///< 日志线程锁
#endif
	ky_log_level_t level;
}ky_log_t;

extern ky_log_t *g_ky_log_default;

/**
 * @brief 打开一个日志
 *
 * @param  log			用来操作日志的结构体
 * @param  logFile		日志文件路径(也可以为: stdout、stderr)
 * @param  openModel	如果logFile是一个文件路径，则这个参数指明打开文件的模式; 否则忽略这个参数
 * @param  level		日志的等级
 * @param  splitType	切割日志的方式: 0 表示不切割; 1 表示按日期切割; 2 表示按大小切割
 * @param  splitSize	超过这个大小(单位:字节)将分割日志
 * @retval 非NULL		表示打开日志成功
 * @retval NULL			表示打开日志失败
 */
extern ky_log_t *ky_log_open(const char *logFile, const char *openMode, ky_log_level_t level, int splitType, long splitSize);
/**
 * @brief 关闭一个日志
 */
extern void ky_log_close(ky_log_t *log);
/**
 * @brief 记录一条日志消息
 * 
 * 日志消息的等级如果比 日志的等级还要高的话，则不作记录
 *
 * @param  log			日志结构体
 * @param  level		日志消息的等级
 * @param  fileName		记录日志的源程序文件名
 * @param  lineNum		记录日志所在的行号
 * @param  format		记录的日志消息，使用方法和printf一样
 */
extern void ky_log_msg(ky_log_t *log, ky_log_level_t level, const char* fileName, int lineNum, const char *format, ...);

/**
 * @brief 重定向stdout、stderr到指定的文件中
 *
 * 注意: 重定向后，往stdout、stderr写入的消息，会先写入到缓冲区，待输出信息达到4K才会写入到重定向的文件中
 *
 * @param  fileName		文件的路径
 * @param  openModel	文件的打开模式
 * @retval 0			表示重定向成功
 * @retval -1			表示重定向失败
 */
extern int ky_log_redirect_std(const char *fileName, const char *openMode);


#ifdef __cplusplus
}
#endif

#endif // _KY_LOG_H
