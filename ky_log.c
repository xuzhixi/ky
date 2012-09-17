#include <string.h>
#include <stdarg.h> 

#include <ky_log.h>
#include <ky_time.h>

ky_log_level_t g_ky_log_std_level;

sint8 ky_log_open(ky_log_t *log, const char *logFile, const char *openModel, ky_log_level_t level)
{
	if ( strcmp(logFile, "stdin") == 0 )
	{
		log->fd = stdin;
	}
	else if ( strcmp(logFile, "stdout") == 0 )
	{
		log->fd = stdout;
	}
	else if ( strcmp(logFile, "stderr") == 0 )
	{
		log->fd = stderr;
	}
	else
	{
		FILE *out;
		if ((out = fopen(logFile, openModel)) == NULL)
		{
			fprintf(stderr, "Cannot open log file: %s\n", logFile);
			return KY_ERROR;
		}
		log->fd = out;
	}
	log->level = level;

	return KY_OK;
}

void ky_log_close(ky_log_t *log)
{
	fclose( log->fd );
}

void ky_log_msg(ky_log_t *log, ky_log_level_t level, const char* fileName, int lineNum, const char *format, ...)
{
	char msg[512];
	char dateTime[20];
	char levelStr[10];
	va_list ap;  

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
			break;
	}

	va_start(ap, format);  
	vsprintf(msg, format, ap); 
	va_end(ap);

	fprintf(log->fd, "%s %s#filename:%s line:%d# %s\n", ky_date_time(dateTime), levelStr, fileName, lineNum, msg);
}

void ky_log_std_init(ky_log_level_t level)
{
	g_ky_log_std_level = level;
}

void ky_log_std_msg(FILE *fd, ky_log_level_t level, const char* fileName, int lineNum, const char *format, ...)
{
	char msg[512];
	char dateTime[20];
	char levelStr[10];
	va_list ap;

	if ( level > g_ky_log_std_level )
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
			break;
	}

	va_start(ap, format);
	vsprintf(msg, format, ap);
	va_end(ap);

	fprintf(fd, "%s %s#filename:%s line:%d# %s\n", ky_date_time(dateTime), levelStr, fileName, lineNum, msg);
}

sint8 ky_log_redirect_std(const char *fileName, const char *openModel)
{
	// 重定向 stdout, stderr
	if (freopen(fileName, openModel, stdout) == NULL)
	{
		fprintf(stderr, "Cann't redirect stream to log file for a!\n");
		return KY_ERROR;
	}
	if (freopen(fileName, openModel, stderr) == NULL)
	{
		fprintf(stderr, "Cann't redirect stream to log file for a!\n");
		return KY_ERROR;
	}

	return KY_OK;
}

