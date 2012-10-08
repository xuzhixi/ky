#include <stdlib.h>
#include <string.h>
#include <stdarg.h> 
#include <sys/stat.h>

#include "ky_log.h"
#include "ky_time.h"


ky_log_t *g_ky_log_default;

static void ky_log_split_name(char *dst, const char *logFileName)
{
	char dateTime[20];

	sprintf(dst, "%s_%s", logFileName, ky_now(dateTime, 20, "yyyy-MM-dd_hh-mm-ss"));
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

ky_log_t *ky_log_open(const char *logFile, const char *openMode, ky_log_level_t level, long splitSize)
{
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
		char splitFileName[150];

		if (splitSize != 0)
		{
			ky_log_split_name(splitFileName, logFile);	
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
	char msg[256];
	char dateTime[20];
	char levelStr[10];
	struct stat fileInfo;
	va_list ap;  

#ifdef __linux
	pthread_mutex_lock( &(log->mutex) );
#endif
	// 分割日志
	if ( log->split_size != 0 && strcmp(log->file_name, "stdout") !=0 && strcmp(log->file_name, "stderr") != 0 )
	{
		fstat(fileno(log->fd), &fileInfo);
		if ( fileInfo.st_size > log->split_size  )
		{
			char splitFileName[150];
			FILE *out;

			ky_log_split_name(splitFileName, log->file_name);
			out = ky_log_open_file(splitFileName, "a");
			if ( out != NULL )
			{
				fclose( log->fd );
				log->fd = out;
			}
		}
	}

	if ( level > log->level )
	{
		return;
	}

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

	//fprintf(log->fd, "%s %-6s#%s\n", ky_now(dateTime, 20, "yyyy-MM-dd hh:mm:ss"), levelStr, msg);
	fprintf(log->fd, "%s %-6s#FileName:%s Line:%d#%s\n", ky_now(dateTime, 20, "yyyy-MM-dd hh:mm:ss"), levelStr, fileName, lineNum, msg);
#ifdef __linux
	 pthread_mutex_unlock( &(log->mutex) );
#endif
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

