#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ky_map.h>
#include <ky_cmp.h>

void preorder_traversal(ky_avltree_s *root)
{
	int *key;
	int *value;

	if ( root != NULL )
	{
		key = root->key;
		value = root->value;
		printf("key: %s value: %d\n", key, *value);
		preorder_traversal(root->left);
		preorder_traversal(root->right);
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
	printf("################################################\n");
	preorder_traversal( rbTree->tree );

	key = "a";
	ky_map_del( rbTree, key );
	printf("################################################\n");
	preorder_traversal( rbTree->tree );
	key = "bb";
	ky_map_del( rbTree, key );
	printf("################################################\n");
	preorder_traversal( rbTree->tree );
	key = "ccc";
	ky_map_del( rbTree, key );
	printf("################################################\n");
	preorder_traversal( rbTree->tree );

	return 0;
}

