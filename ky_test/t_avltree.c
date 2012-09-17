#include <stdio.h>

#include <ky_avltree.h>
#include <ky_cmp.h>

void preorder_traversal(ky_avltree_s *root)
{
	int *key;
	int *value;

	if ( root != NULL )
	{
		key = root->key;
		value = root->value;
		printf("key: %d value: %d\n", *key, *value);
		preorder_traversal(root->left);
		preorder_traversal(root->right);
	}
}

//void inorder_traversal()
//{
//}
//
//void postorder_traversal()
//{
//}

int main()
{
	ky_avltree_t *avlTree;
	int isQuit = 0;
	int key;
	int value;
	uint8 c;

	avlTree = ky_avltree_new(sizeof(int), sizeof(int), ky_cmp_int);
	while (1)
	{
		printf("\n\n1. add\n2. mod\n3. del\n4. show data\n5. quit\nplease input your choise: ");
		scanf("%d", &c);
		switch ( c )
		{
			case 1:
				printf("please input yout key and value: ");
				scanf("%d %d", &key, &value);	
				ky_avltree_add( avlTree, &key, &value );
				break;
			case 2:
				printf("please input your key and value: ");
				scanf("%d %d", &key, &value);	
				ky_avltree_mod( avlTree, &key, &value );
				break;
			case 3:
				printf("please input yout key: ");
				scanf("%d", &key);	
				ky_avltree_del( avlTree, &key );
				break;
			case 4:
				printf("################################################\n");
				preorder_traversal( avlTree->tree );
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
			ky_avltree_release( avlTree );
			break;
		}
	}

	return 0;
}
