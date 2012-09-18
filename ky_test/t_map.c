#include <stdio.h>
#include <stdlib.h>

#include <ky_map.h>
#include <ky_cmp.h>

#define color_str(node) (node->color == 0 ? "red" : "black") 

// 先序遍历
void preorder_traversal(ky_rbtree_s *root)
{
	int *key;
	int *value;

	if ( root != ky_rbtree_nil )
	{
		key = root->key;
		value = root->value;
		printf( "key: %d value: %d color: %s\n", *key, *value, color_str(root) );
		preorder_traversal(root->left);
		preorder_traversal(root->right);
	}
}

// 测试是否存在两个相邻的红色节点
void test_two_red(ky_rbtree_s *root)
{
	int *key;
	int *value;

	if ( root != ky_rbtree_nil )
	{
		if ( root->color == KY_RBTREE_RED )
		{
			if ( root->left->color == KY_RBTREE_RED )
			{
				printf("存在两个相邻的红色节点!!!key1: %d key2: %d\n", *(int *)(root->key), *(int *)(root->left->key));
			}
			else if ( root->right->color == KY_RBTREE_RED )
			{
				printf("存在两个相邻的红色节点!!!key1: %d key2: %d\n", *(int *)(root->key), *(int *)(root->right->key));
			}

		}
		test_two_red(root->left);
		test_two_red(root->right);
	}
}

// 获取黑色路径的长度, 及测试各路径黑色节点数目是否一致
int black_count(ky_rbtree_s *root)
{
	if ( root == ky_rbtree_nil )
	{
		return 1;
	}
	else
	{
		int left_black_count;
		int right_black_count;

		left_black_count = black_count(root->left);
		right_black_count = black_count(root->right);
		if ( root->color == KY_RBTREE_RED )
		{
			if ( left_black_count == right_black_count )
			{
				return left_black_count;
			}	
			else
			{
				printf("某路径黑色节点数目不一致!!!key: %d\n", *(int *)(root->key));
				return -1;
			}
		}
		else
		{
			if ( left_black_count == right_black_count )
			{
				return left_black_count + 1;
			}	
			else
			{
				printf("某路径黑色节点数目不一致!!!key: %d\n", *(int *)(root->key));
				return -1;
			}
		}
	}
}


int main()
{
	ky_map_t *rbTree;
	int isQuit = 0;
	int key;
	int value;
	uint8 c;
	int i;

	rbTree = ky_map_new(sizeof(int), sizeof(int), ky_cmp_int);

	srand( time(NULL) );
	for (i=0; i<50; i++)		// 随机插入
	{
		key = rand() % 100;
		value = rand() % 1000;
		ky_map_add( rbTree, &key, &value );
		test_two_red( rbTree->tree );	// 每次插入都进行测试
		black_count( rbTree->tree );
	}
	test_two_red( rbTree->tree );
	printf("黑色路径长度: %d\n", black_count( rbTree->tree ) );
	//printf("################################################\n");
	//preorder_traversal( rbTree->tree );
	//printf("################################################\n\n");

	for (i=0; i<200; i++)		// 随机删除
	{
		key = rand() % 100;
		ky_map_del( rbTree, &key );
		test_two_red( rbTree->tree );	// 每次删除都进行测试
		black_count( rbTree->tree );
	}
	test_two_red( rbTree->tree );
	printf("黑色路径长度: %d\n", black_count( rbTree->tree ) );
	printf("################################################\n");
	preorder_traversal( rbTree->tree );
	printf("################################################\n");

	/*
	while (1)
	{
		printf("\n\n1. add\n2. mod\n3. del\n4. show data\n5. quit\nplease input your choise: ");
		scanf("%d", &c);
		switch ( c )
		{
			case 1:
				printf("please input yout key and value: ");
				scanf("%d %d", &key, &value);	
				ky_rbtree_add( rbTree, &key, &value );
				break;
			case 2:
				printf("please input your key and value: ");
				scanf("%d %d", &key, &value);	
				ky_rbtree_mod( rbTree, &key, &value );
				break;
			case 3:
				printf("please input yout key: ");
				scanf("%d", &key);	
				ky_rbtree_del( rbTree, &key );
				break;
			case 4:
				printf("################################################\n");
				preorder_traversal( rbTree->tree );
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
			ky_rbtree_release( rbTree );
			break;
		}
	}
	*/

	return 0;
}

