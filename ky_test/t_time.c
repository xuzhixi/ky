#include <stdio.h>

#include <ky_time.h>

int main()
{
	char nowTime[20];

	ky_date_time( nowTime );
	printf("now %s\n", nowTime );

	return 0;
}

