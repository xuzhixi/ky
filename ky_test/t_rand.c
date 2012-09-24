#include <stdio.h>
#include <stdlib.h>

#include <ky_core.h>

int main()
{
	int i;
	int minute;

	//srand( time(NULL) );
	//for (i=0; i<10; i++)
	//{
	//	minute = ( rand() % 9 ) + 1;
	//	printf("minute: %d\n", minute);
	//}
	
	printf("RAND_MAX: %d result: %d\n", RAND_MAX, ky_rand(1,9));

	return 0;
}
