#include <stdio.h>
#include <ky_string.h>

int main()
{
	ky_str_t *name = ky_str_new("XiaoMing");

	printf("name: %s\n", name->s);
	ky_str_toupper( name );
	printf("upper name: %s\n", name->s);
	ky_str_tolower( name );
	printf("lower name: %s\n", name->s);
	ky_str_release( name );

	return 0;
}
	
