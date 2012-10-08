#include <stdio.h>
#include "ky_opt.h"

int main(int argc, char *argv[])
{
	if ( ky_preopt(argc, argv, "ab:c:de::") )
	{
		printf("succefully!\n");
	}
	else
	{
		printf("fail!\n");
	}

	return 0;
}

