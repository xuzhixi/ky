//===============================================
/**
 *  @file ky_log.c
 *
 *  @author XuZhiXi
 *  Email   932834199@qq.com or 932834199@163.com
 *
 *  Create datetime:  2012-10-17 08:11:50
 *  Last   modified:  2012-10-25 23:55:41
 *
 *  Description: 
 */
//================================================

#include <stdlib.h>
#include <string.h>
#include <stdarg.h> 
#include <sys/stat.h>

#include "ky_log.h"
#include "ky_time.h"


ky_log_t *g_ky_log_default = NULL;

static void ky_log_split_name(char *dst, const char *logFileName, int splitType)
{
	char dateTime[20];

	if ( splitType == 1 )
	{
		sprintf(dst, "%s_%s", logFileName, ky_now(dateTime, 20, "yyyy-MM-dd"));
	}
	else if ( splitType == 2 )
	{
		sprintf(dst, "%s_%s", logFileName, ky_now(dateTime, 20, "yyyy-MM-dd_hh-mm-ss"));
	}
}

static FILE *ky_log_open_file(const char *fileName, const char *openMode)
{
	FILE *fd;
	
	if ((fd = fopen(fileName, openMode)) == NULL)
	{
		fprintf(stderr, "Can not open log file: %s\n", fileName);
		return NULL;
	}

	return fd;
}

ky_log_t *ky_log_open(const char *logFile, const char *openMode, ky_log_level_t level, int splitType, long splitSize)
{
	ky_time_t t;
	ky_log_t *log;
	FILE *out;

	if ( strcmp(logFile, "stdout") == 0 )
	{
		out = stdout;
	}
	else if ( strcmp(logFile, "stderr") == 0 )
	{
		out = stderr;
	}
	else
	{
		char splitFileName[KY_LOG_FILENAME_MAXSIZE];

		if (splitType != 0)
		{
			ky_localtime( &t );
			ky_log_split_name(splitFileName, logFile, splitType);	
			out = ky_log_open_file(splitFileName, openMode);
		}
		else
		{
			out = ky_log_open_file(logFile, openMode);
		}

		if ( out == NULL )
		{
			return NULL;
		}
	}

	log = (ky_log_t *)malloc( sizeof(ky_log_t) );
	log->file_name = (char *)malloc( strlen(logFile)+1 );
	strcpy(log->file_name, logFile);
	log->fd = out;
	log->level = level;
	log->split_type = splitType;
	log->day		= t.day;
	log->split_size = splitSize;
#ifdef __linux
	pthread_mutex_init( &(log->mutex), NULL );
#endif

	return log;
}

void ky_log_close(ky_log_t *log)
{
	if ( log->fd != stdout && log->fd != stderr )
	{
		fclose( log->fd );
	}
#ifdef __linux
	pthread_mutex_destroy( &(log->mutex) );
#endif
	free( log->file_name );
	free( log );
}

void ky_log_msg(ky_log_t *log, ky_log_level_t level, const char* fileName, int lineNum, const char *format, ...)
{
	char msg[KY_LOG_MSG_MAXSIZE];
	char dateTime[20];
	char levelStr[10];
	ky_time_t t;
	struct stat fileInfo;
	va_list ap;  

	switch ( level )
	{
		case KY_LOG_LEVEL_FATAL:
			strcpy( levelStr, "FATAL" );
			break;
		case KY_LOG_LEVEL_ERROR:
			strcpy( levelStr, "ERROR" );
			break;
		case KY_LOG_LEVEL_WARN: 
			strcpy( levelStr, "WARN" );
			break;
		case KY_LOG_LEVEL_INFO:
			strcpy( levelStr, "INFO" );
			break;
		case KY_LOG_LEVEL_DEBUG:
			strcpy( levelStr, "DEBUG" );
			break;
		default:
			strcpy( levelStr, "UNKNOWN" );
			break;
	}

	va_start(ap, format);
	vsprintf(msg, format, ap); 
	va_end(ap);

	if ( log == NULL )	// 默认的日志输出方式
	{
		//fprintf(stdout, "%s %-6s#%s\n", ky_now(dateTime, 20, "yyyy-MM-dd hh:mm:ss"), levelStr, msg);
		fprintf(stdout, "%s %-6s#FileName:%s Line:%d#%s\n", ky_now(dateTime, 20, "yyyy-MM-dd hh:mm:ss"), levelStr, fileName, lineNum, msg);
		return;
	}

#ifdef __linux
	pthread_mutex_lock( &(log->mutex) );
#endif
	// 按日分割日志
	if ( log->split_type != 0 && strcmp(log->file_name, "stdout") !=0 && strcmp(log->file_name, "stderr") != 0 )
	{
		char splitFileName[KY_LOG_FILENAME_MAXSIZE];
		FILE *out;

		if ( log->split_type == 1 )
		{
			ky_localtime( &t );			
			if ( log->day != t.day )
			{
				ky_log_split_name(splitFileName, log->file_name, log->split_type);
				out = ky_log_open_file(splitFileName, "a");
				if ( out != NULL )
				{
					fclose( log->fd );
					log->fd = out;
				}
			}
		}
		else if ( log->split_type == 2 )	// 按大小分割日志
		{
			fstat(fileno(log->fd), &fileInfo);
			if ( fileInfo.st_size > log->split_size  )
			{
				ky_log_split_name(splitFileName, log->file_name, log->split_type);
				out = ky_log_open_file(splitFileName, "a");
				if ( out != NULL )
				{
					fclose( log->fd );
					log->fd = out;
				}
			}
		}
	}

	if ( level > log->level )
	{
		return;
	}
#ifdef __linux
	 pthread_mutex_unlock( &(log->mutex) );
#endif

	//fprintf(log->fd, "%s %-6s#%s\n", ky_now(dateTime, 20, "yyyy-MM-dd hh:mm:ss"), levelStr, msg);
	fprintf(log->fd, "%s %-6s#FileName:%s Line:%d#%s\n", ky_now(dateTime, 20, "yyyy-MM-dd hh:mm:ss"), levelStr, fileName, lineNum, msg);
}

int ky_log_redirect_std(const char *fileName, const char *openMode)
{
	// 重定向 stdout, stderr
	if (freopen(fileName, openMode, stdout) == NULL)
	{
		fprintf(stderr, "Can not redirect stream to log file for a!\n");
		return -1;
	}
	if (freopen(fileName, openMode, stderr) == NULL)
	{
		fprintf(stderr, "Can not redirect stream to log file for a!\n");
		return -1;
	}

	return 0;
}

