#ifndef _KY_LOG_H
#define _KY_LOG_H

#include <stdio.h>
#include <ky_types.h>

#define KY_LOG_DEBUG(log, format, ...) ky_log_msg(log, KY_LOG_LEVEL_DEBUG, __FILE__, __LINE__, format, ##__VA_ARGS__) 
#define KY_LOG_INFO(log, format, ...)  ky_log_msg(log, KY_LOG_LEVEL_INFO,  __FILE__, __LINE__, format, ##__VA_ARGS__)
#define KY_LOG_WARN(log, format, ...)  ky_log_msg(log, KY_LOG_LEVEL_WARN,  __FILE__, __LINE__, format, ##__VA_ARGS__)
#define KY_LOG_ERROR(log, format, ...) ky_log_msg(log, KY_LOG_LEVEL_ERROR, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define KY_LOG_FATAL(log, format, ...) ky_log_msg(log, KY_LOG_LEVEL_FATAL, __FILE__, __LINE__, format, ##__VA_ARGS__)

#define KY_LOG_STD_DEBUG(format, ...) ky_log_std_msg(stderr, KY_LOG_LEVEL_DEBUG, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define KY_LOG_STD_INFO(format, ...)  ky_log_std_msg(stderr, KY_LOG_LEVEL_INFO,  __FILE__, __LINE__, format, ##__VA_ARGS__)
#define KY_LOG_STD_WARN(format, ...)  ky_log_std_msg(stderr, KY_LOG_LEVEL_WARN,  __FILE__, __LINE__, format, ##__VA_ARGS__)
#define KY_LOG_STD_ERROR(format, ...) ky_log_std_msg(stderr, KY_LOG_LEVEL_ERROR, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define KY_LOG_STD_FATAL(format, ...) ky_log_std_msg(stderr, KY_LOG_LEVEL_FATAL, __FILE__, __LINE__, format, ##__VA_ARGS__)

#ifdef _CPLUSPLUS
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
	uint8 level;
}ky_log_t;

extern ky_log_level_t g_ky_log_std_level;

/**
 * @brief 打开一个日志
 *
 * @param  log			用来操作日志的结构体
 * @param  logFile		日志文件路径(也可以为: stdin、stdout、stderror)
 * @param  openModel	如果logFile是一个文件路径，则这个参数指明打开文件的模式; 否则忽略这个参数
 * @param  level		日志的等级
 * @retval KY_OK		表示打开日志成功
 * @retval KY_ERROR		表示打开日志失败
 */
extern sint8 ky_log_open(ky_log_t *log, const char *logFile, const char *openModel, ky_log_level_t level);
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
 * @retval KY_OK		表示重定向成功
 * @retval KY_ERROR		表示重定向失败
 */
extern sint8 ky_log_redirect_std(const char *fileName, const char *openModel);

/**
 * @brief 初始化stdout和stderr，输出日志的等级
 */
extern void ky_log_std_init(ky_log_level_t level);
/**
 * @brief 与ky_log_msg类似，不同的是: 第一个参数是stdout或者stderr
 *
 * @see ky_log_msg()
 */
extern void ky_log_std_msg(FILE *fd, ky_log_level_t level, const char* fileName, int lineNum, const char *format, ...);

#ifdef _CPLUSPLUS
}
#endif

#endif // _KY_LOG_H
