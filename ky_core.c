#include <stdlib.h>
#include <time.h>

#include <ky_core.h>


uint32 ky_rand(uint32 start, uint32 end)
{
	uint32 scopeCount;
	uint32 result;

	scopeCount = end - start + 1;
	srand( time(NULL) );
	result = ( rand() % scopeCount  ) + start;

	return result;
}

