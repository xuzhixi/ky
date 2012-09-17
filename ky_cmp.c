#include <ky_types.h>
#include <ky_cmp.h>

sint8 ky_cmp_int(void *val1, void *val2)
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
