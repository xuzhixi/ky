#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ky_log.h"
#include "ky_tool.h"


unsigned int ky_rand(unsigned int start, unsigned int end)
{
	unsigned int scopeLen;
	unsigned int result;

	scopeLen = end - start + 1;
	srand( time(NULL) );
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

	return 0;
}
