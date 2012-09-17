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

typedef struct ky_log_t
{
	FILE *fd;	
	uint8 level;
}ky_log_t;

extern ky_log_level_t g_ky_log_std_level;

extern sint8 ky_log_open(ky_log_t *log, const char *logFile, const char *openModel, ky_log_level_t level);
extern void ky_log_close(ky_log_t *log);
extern void ky_log_msg(ky_log_t *log, ky_log_level_t level, const char* fileName, int lineNum, const char *format, ...);

extern void ky_log_std_init(ky_log_level_t level);
extern void ky_log_std_msg(FILE *fd, ky_log_level_t level, const char* fileName, int lineNum, const char *format, ...);
extern sint8 ky_log_redirect_std(const char *fileName, const char *openModel);

#ifdef _CPLUSPLUS
}
#endif

#endif // _KY_LOG_H
