#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
		printf( "key: %s value: %d color: %s\n", key, *value, color_str(root) );
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
	char *key;
	int value;

	rbTree = ky_map_new(sizeof(int), sizeof(int), ky_cmp_str);

	key = "a";
	value = 1;
	ky_map_addv( rbTree, key, strlen(key)+1, &value, sizeof(int) );
	key = "bb";
	value = 2;
	ky_map_addv( rbTree, key, strlen(key)+1, &value, sizeof(int) );
	key = "ccc";
	value = 3;
	ky_map_addv( rbTree, key, strlen(key)+1, &value, sizeof(int) );
	test_two_red( rbTree->tree );
	printf("黑色路径长度: %d\n", black_count( rbTree->tree ) );
	printf("################################################\n");
	preorder_traversal( rbTree->tree );
	printf("################################################\n");

	key = "a";
	ky_map_del( rbTree, key );
	test_two_red( rbTree->tree );
	printf("黑色路径长度: %d\n", black_count( rbTree->tree ) );
	preorder_traversal( rbTree->tree );
	key = "bb";
	ky_map_del( rbTree, key );
	test_two_red( rbTree->tree );
	printf("黑色路径长度: %d\n", black_count( rbTree->tree ) );
	preorder_traversal( rbTree->tree );
	key = "ccc";
	ky_map_del( rbTree, key );
	test_two_red( rbTree->tree );
	printf("黑色路径长度: %d\n", black_count( rbTree->tree ) );
	preorder_traversal( rbTree->tree );
	
	return 0;
}

