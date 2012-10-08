#include <stdio.h>
#include "ky_tool.h"

int main()
{
	char condition[30];

	ky_memzero( condition, sizeof(condition) );
	printf("condition: %s\n", condition);

	return 0;
}
