//===============================================
/**
 *  @file ky_opt.c
 *
 *  @author XuZhiXi
 *  Email   932834199@qq.com or 932834199@163.com
 *
 *  Create datetime:  2012-10-17 08:12:36
 *  Last   modified:  2012-10-17 08:12:36
 *
 *  Description: 
 */
//================================================

#include <unistd.h>
#include <stdio.h>
#include "ky_opt.h"


/**
 * optstring: "ab:c:de::"
 * 1.单个字符，表示选项，
 * 2.单个字符后接一个冒号,表示该选项后必须跟一个参数. 参数紧跟在选项后或者以空格隔开。该参数的指针赋给optarg。
 * 3 单个字符后跟两个冒号,表示该选项后必须跟一个参数. 参数必须紧跟在选项后不能以空格隔开。该参数的指针赋给optarg。
 */
int ky_preopt(int argc, char *const argv[], const char *optstring)
{
	char c;

	while ((c = getopt(argc, argv, optstring)) != -1)
	{
		switch (c) 
		{
			case 'a':
				printf("have option: -%c\n\n", c);
				break;
			case 'b':
				printf("have option: -%c\n\n", c);
				if ( optarg == NULL || optarg[0] == '-' )
				{
					printf("option: -b can not is null\n\n");
					return -1;
				}
				else
				{
					printf("The argument of -b is %s\n\n", optarg);
				}
				break;
			case 'c':
				printf("have option: -%c\n\n", c);
				if ( optarg == NULL || optarg[0] == '-' )
				{
					printf("option: -c can not is null\n\n");
					return -1;
				}
				else
				{
					printf("The argument of -c is %s\n\n", optarg);
				}
				break;
			case 'd':
				printf("have option: -%c\n\n", c);
				break;
			case 'e':
				printf("have option: -%c\n\n", c);
				if ( optarg == NULL || optarg[0] == '-' )
				{
					printf("option: -e can not is null\n\n");
					return -1;
				}
				else
				{
					printf("The argument of -e is %s\n\n", optarg);
				}
				break;
			case '?':
				printf("Invalid option: -%c\n\n", (char)optopt);
				return -1;
				break;
			default:
				break;
		}
	}

	return 0;
}
