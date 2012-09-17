#include <stdio.h>

#include <ky_linklist.h>
#include <ky_cmp.h>

void print_linklist(ky_linklist_t *linklist)
{
	ky_linklist_s *p;
	int *value;
	
	p = linklist->head;
	while ( p != NULL )
	{
		value = (int *)(p->value);
		printf("%d ", *value);
		p = p->next;
	}
	printf("\n");
}

int main()
{
	ky_linklist_t *linklist;
	int isQuit = 0;
	int value;
	int insertValue;
	uint8 c;

	linklist = ky_linklist_new(sizeof(int), ky_cmp_int);
	while (1)
	{
		printf("1. add\n2. insert\n3. del\n4. show data\n5. quit\nplease input your choise: ");
		scanf("%d", &c);
		switch ( c )
		{
			case 1:
				printf("please input your add value: ");
				scanf("%d", &value);	
				ky_linklist_add( linklist, &value );
				break;
			case 2:
				printf("please input your localtion value and insert value: ");
				scanf("%d %d", &value, &insertValue);	
				ky_linklist_insert( linklist, &value, &insertValue );
				break;
			case 3:
				printf("please input your delete value: ");
				scanf("%d", &value);	
				ky_linklist_del( linklist, &value );
				break;
			case 4:
				printf("################################################\n");
				print_linklist( linklist );
				printf("################################################\n");
				break;
			case 5:
				isQuit = 1;
				break;
			default:
				break;
		}

		if ( isQuit == 1 )
		{
			ky_linklist_release( linklist );
			break;
		}
	}

	return 0;
}
