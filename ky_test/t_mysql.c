#include <stdio.h>
#include "ky_mysql.h"
#include "ky_log.h"
#include "ky_tool.h"

int main()
{
	ky_mysql_t *my;
	char sql[256];

	ky_log_open_default("stdout", "a", KY_LOG_LEVEL_ALL, 0);
	ky_save_pid_file("t_mysql_pid");
	g_ky_mysql_is_debug = 1;
	my = ky_mysql_new(5);
	if ( ky_mysql_connect( my, "192.168.136.1", "root", "2185530", "test", 3306 ) )
	{
		printf("auto id: %lu\n", ky_mysql_execute_id(my, "insert into user(name,age) values('888', 888)"));
		printf("testtest\n");
		printf("affected rows: %lu\n", ky_mysql_affected_rows(my));
		if ( ky_mysql_select( my , "select id,name,age from user" ) )
		{
			printf("affected rows: %lu\n", ky_mysql_affected_rows(my));
			while ( ky_mysql_next(my) )
			{
				int id;
				char name[30];
				int age;

				id = ky_mysql_get_int( my, "id" );
				ky_mysql_get_char( my, "name", name, sizeof(name) );
				age = ky_mysql_get_int( my, "age" );
				printf("id: %d name: %s age: %d\n", id, name, age);
			}
		}
	}
	ky_mysql_release( my );
	ky_log_close_default();
}

