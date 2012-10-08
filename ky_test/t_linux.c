#include <stdio.h>

int main()
{

#ifdef __linux
	printf("linux\n");
#endif
#ifdef __WIN32
	printf("win32\n");
#endif

	return 0;
}
