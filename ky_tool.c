//===============================================
/**
 *  @file ky_tool.c
 *
 *  @author XuZhiXi
 *  Email   932834199@qq.com or 932834199@163.com
 *
 *  Create datetime:  2012-10-17 08:15:29
 *  Last   modified:  2012-10-17 08:15:29
 *
 *  Description: 
 */
//================================================

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ky_log.h"
#include "ky_tool.h"


unsigned int ky_rand(unsigned int start, unsigned int end)
{
	static time_t lastTime = 0;
	unsigned int scopeLen;
	unsigned int result;

	scopeLen = end - start + 1;
	if ( lastTime != time(NULL) )
	{
		lastTime = time(NULL);
		srand( lastTime );
	}
	result = ( rand() % scopeLen  ) + start;

	return result;
}

void *ky_memzero(void *s, size_t n)
{
	return memset(s, 0, n);	
}

int ky_save_pid_file(const char *fileName)
{
	FILE *fp;

	if ( (fp=fopen(fileName, "w")) == NULL )
	{
		KY_LOG_WARN("open pidfile: %s error!", fileName);
		return -1;
	}
	fprintf(fp, "%d\n",  getpid());
	fclose(fp);

	return 0;
}
