#include <stdlib.h>

#include <ky_malloc.h>

void *ky_malloc(size_t size)
{
	return malloc( size );
}

void ky_free(void *ptr)
{
	free( ptr );
}

