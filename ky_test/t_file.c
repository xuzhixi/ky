#include <stdio.h>
#include <ky_file.h>

int main()
{
	ky_file_t *file;
	ky_str_t *line;

	file = ky_file_open("t_mysql.c", "r");
	//while ( (line = (ky_str_t *)ky_file_read_line(file)) )
	//{
	//	printf("%s", line->s);
	//}
	line = (ky_str_t *)ky_file_read_all( file );
	printf("%s", line->s);
	ky_file_close( file );

	return 0;
}
	
