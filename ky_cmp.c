#include <string.h>
#include "ky_cmp.h"

int ky_cmp_int(void *val1, void *val2)
{
	int *value1 = val1;
	int *value2 = val2;

	if ( *value1 > *value2 )
	{
		return 1;
	}
	else if ( *value1 < *value2 )
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

int ky_cmp_str(void *val1, void *val2)
{
	return strcmp(val1, val2);
}
