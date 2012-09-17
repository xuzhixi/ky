#include <string.h>

#include <ky_math.h>
#include <ky_malloc.h>
#include <ky_avltree.h>

static ky_avlnode_s *ky_avltree_node_new_i(void *key, ky_avltree_key_len_t keyLen, void *value, ky_avltree_value_len_t valueLen)
{
	ky_avlnode_s *node;

	node = (ky_avlnode_s *)ky_malloc( sizeof(ky_avlnode_s) );
	node->left = NULL;
	node->right = NULL;
	node->height = 0;
	node->key = ky_malloc( keyLen );
	memcpy( node->key, key, keyLen );
	node->value = ky_malloc( valueLen );
	memcpy( node->value, value, valueLen );

	return node;
}

static void ky_avltree_node_delete_i(ky_avlnode_s *node)
{
	ky_free( node->key );
	ky_free( node->value );
	ky_free( node );
}

static void ky_avltree_release_i(ky_avltree_s *root)
{
	if ( root != NULL )
	{
		ky_avltree_release_i( root->left );
		ky_avltree_release_i( root->right );
		ky_avltree_node_delete_i( root );
	}
}

static ky_avltree_height_t ky_avltree_height_i(ky_avltree_s *node)
{
	if ( node == NULL )
	{
		return -1;
	}
	else
	{
		return node->height;
	}
}

static ky_avltree_s *ky_single_rotate_with_left_i(ky_avltree_s *root)
{
	ky_avlnode_s *lNode;

	lNode = root->left;
	root->left = lNode->right;
	lNode->right = root;

	root->height = ky_max( ky_avltree_height_i(root->left), ky_avltree_height_i(root->right) ) + 1;
	lNode->height = ky_max( ky_avltree_height_i(lNode->left), ky_avltree_height_i(lNode->right) ) + 1;

	return lNode;
}

static ky_avltree_s *ky_single_rotate_with_right_i(ky_avltree_s *root)
{
	ky_avlnode_s *rNode;

	rNode = root->right;
	root->right = rNode->left;
	rNode->left = root;

	root->height = ky_max( ky_avltree_height_i(root->left), ky_avltree_height_i(root->right) ) + 1;
	rNode->height = ky_max( ky_avltree_height_i(rNode->left), ky_avltree_height_i(rNode->right) ) + 1;

	return rNode;
}

static ky_avltree_s *ky_double_rotate_with_left_i(ky_avltree_s *root)
{
	root->left = ky_single_rotate_with_right_i(root->left);
	return ky_single_rotate_with_left_i(root);
}


static ky_avltree_s *ky_double_rotate_with_right_i(ky_avltree_s *root)
{
	root->right = ky_single_rotate_with_left_i(root->right);
	return ky_single_rotate_with_right_i(root);
}

static ky_avlnode_s *ky_avltree_find_i(ky_avltree_s *root, void *key, ky_avltree_comparefun_t cmpFun)
{
	sint8 cmpResult;

	while ( root != NULL && (cmpResult = cmpFun(root->key, key)) != 0 )
	{
		if ( cmpResult > 0 )
		{
			root = root->left;
		}
		else if ( cmpResult < 0 )
		{
			root = root->right;
		}
	}

	return root;
}

static ky_avlnode_s *ky_avltree_find_max_i(ky_avltree_s *root)
{
	while ( root != NULL && root->right != NULL )
	{
		root = root->right;
	}

	return root;
}

static ky_avlnode_s *ky_avltree_find_min_i(ky_avltree_s *root)
{
	while ( root != NULL && root->left != NULL )
	{
		root = root->left;
	}

	return root;
}

static ky_avltree_s *ky_avltree_add_i(ky_avltree_s *root, void *value, ky_avltree_value_len_t valueLen, void *key, ky_avltree_key_len_t keyLen, ky_avltree_comparefun_t cmpFun)
{
	sint8 cmpResult;

	if ( root == NULL )
	{
		root = ky_avltree_node_new_i(key, keyLen, value, valueLen);
		return root;
	}

	cmpResult = cmpFun(root->key, key);
	if ( cmpResult > 0 )
	{
		root->left = ky_avltree_add_i(root->left, value, valueLen, key, keyLen, cmpFun);
		if ( ky_avltree_height_i(root->left) - ky_avltree_height_i(root->right) == 2 )
		{
			if ( cmpFun(root->left->key, key) > 0 )
			{
				root = ky_single_rotate_with_left_i( root );	// 左单旋
			}
			else
			{
				root = ky_double_rotate_with_left_i( root );	// 左双旋
			}
		}
	}
	else if ( cmpResult < 0 )
	{
		root->right = ky_avltree_add_i(root->right, value, valueLen, key, keyLen, cmpFun);
		if ( ky_avltree_height_i(root->right) - ky_avltree_height_i(root->left) == 2 )
		{
			if ( cmpFun(root->right->key, key) < 0 )
			{
				root = ky_single_rotate_with_right_i( root );	// 右单旋
			}
			else
			{
				root = ky_double_rotate_with_right_i( root );	// 右双旋
			}
		}
	}

	root->height = ky_max( ky_avltree_height_i(root->left), ky_avltree_height_i(root->right) ) + 1;

	return root;
}

static ky_avltree_s *ky_avltree_mod_i(ky_avltree_s *root, void *value, ky_avltree_value_len_t valueLen, void *key, ky_avltree_key_len_t keyLen, ky_avltree_comparefun_t cmpFun)
{
	ky_avlnode_s *tNode;

	tNode = ky_avltree_find_i(root, key, cmpFun);
	if ( tNode == NULL )
	{
		root = ky_avltree_add_i(root, value, valueLen, key, keyLen, cmpFun);
	}
	else
	{
		memcpy(tNode->value, value, valueLen);
	}

	return root;
}

//static void ky_avltree_del_assist_i(ky_avltree_s *root, ky_avltree_key_len_t keyLen, ky_avltree_value_len_t valueLen)
//{
//	ky_avltree_s *parentNode;
//	ky_avltree_s *nextNode;
//
//	parentNode = root;
//	nextNode = root->left;
//	while ( nextNode->right != NULL )
//	{
//		parentNode = nextNode;
//		nextNode = nextNode->right;
//	}
//
//	memcpy(root->key, nextNode->key, keyLen);
//	memcpy(root->value, nextNode->value, valueLen);
//	ky_avltree_node_delete_i(nextNode);
//	if ( parentNode == root )
//	{
//		parentNode->left = NULL;
//	}
//	else
//	{
//		parentNode->right = NULL;
//	}
//}

static ky_avltree_s *ky_avltree_del_i(ky_avltree_s *root, void *key, ky_avltree_key_len_t keyLen, ky_avltree_value_len_t valueLen, ky_avltree_comparefun_t cmpFun)
{
	sint8 cmpResult;

	if ( root == NULL )
	{
		return NULL;
	}

	cmpResult = cmpFun(root->key, key);
	if ( cmpResult > 0 )
	{
		root->left = ky_avltree_del_i(root->left, key, keyLen, valueLen, cmpFun);
		if ( ky_avltree_height_i(root->right) - ky_avltree_height_i(root->left) == 2 )
		{
			if ( ky_avltree_height_i(root->right->right) > ky_avltree_height_i(root->right->left) )
			{
				root = ky_single_rotate_with_right_i( root );   // 右单旋
			}
			else
			{
				root = ky_double_rotate_with_right_i( root );   // 右双旋
			}
		}

	}
	else if ( cmpResult < 0 )
	{
		root->right = ky_avltree_del_i(root->right, key, keyLen, valueLen, cmpFun);
		if ( ky_avltree_height_i(root->left) - ky_avltree_height_i(root->right) == 2 )
		{
			if ( ky_avltree_height_i(root->left->left) > ky_avltree_height_i(root->left->right) )
			{
				root = ky_single_rotate_with_left_i( root );    // 左单旋
			}
			else
			{
				root = ky_double_rotate_with_left_i( root );    // 左双旋
			}
		}
	}
	else
	{
		ky_avlnode_s *tNode;

		if ( root->left !=NULL && root->right != NULL )
		{
			tNode = ky_avltree_find_max_i(root->left);
			memcpy(root->key, tNode->key, keyLen);
			memcpy(root->value, tNode->value, valueLen);
			root->left = ky_avltree_del_i(root->left, tNode->key, keyLen, valueLen, cmpFun);
			if ( ky_avltree_height_i(root->right) - ky_avltree_height_i(root->left) == 2 )
			{
				if ( ky_avltree_height_i(root->right->right) > ky_avltree_height_i(root->right->left) )
				{
					root = ky_single_rotate_with_right_i( root );   // 右单旋
				}
				else
				{
					root = ky_double_rotate_with_right_i( root );   // 右双旋
				}
			}
			//ky_avltree_del_assist_i(root, keyLen, valueLen);
		}
		else if ( root->left != NULL )
		{
			tNode = root->left;
			ky_avltree_node_delete_i( root );
			return tNode;
		}
		else
		{
			tNode = root->right;
			ky_avltree_node_delete_i( root );
			return tNode;
		}
	}

	root->height = ky_max( ky_avltree_height_i(root->left), ky_avltree_height_i(root->right) ) + 1;

	return root;
}

ky_avltree_t *ky_avltree_new(ky_avltree_key_len_t keyLen, ky_avltree_value_len_t valueLen, ky_avltree_comparefun_t cmpFun)
{
	ky_avltree_t *avltree;

	avltree =  (ky_avltree_t *)ky_malloc( sizeof(ky_avltree_t) );
	avltree->key_len = keyLen;
	avltree->value_len = valueLen;
	avltree->cmp_fun = cmpFun;
	avltree->tree = NULL;

	return avltree;
}

void ky_avltree_clear(ky_avltree_t *avltree)
{
	ky_avltree_release_i( avltree->tree );
	avltree->tree = NULL;
}

void ky_avltree_release(ky_avltree_t *avltree)
{
	ky_avltree_clear( avltree );
	ky_free( avltree );
}

bool ky_avltree_is_null(ky_avltree_t *avltree)
{
	if ( avltree->tree == NULL )
	{
		return KY_TRUE;
	}
	else
	{
		return KY_FALSE;
	}
}

void *ky_avltree_find(ky_avltree_t *avltree, void *key)
{
	ky_avlnode_s *node;

	node = ky_avltree_find_i(avltree->tree, key, avltree->cmp_fun);
	if ( node == NULL )
	{
		return NULL;
	}
	else
	{
		return node->value;
	}
}

void *ky_avltree_find_max(ky_avltree_t *avltree)
{
	ky_avlnode_s *node;

	node = ky_avltree_find_max_i( avltree->tree ); 
	if ( node == NULL )
	{
		return NULL;
	}
	else
	{
		return node->value;
	}
}

void *key_avltree_find_min(ky_avltree_t *avltree)
{
	ky_avlnode_s *node;

	node = ky_avltree_find_min_i(avltree->tree);
	if ( node == NULL )
	{
		return NULL;
	}
	else
	{
		return node->value;
	}
}

void ky_avltree_add(ky_avltree_t *avltree, void *key, void *value)
{
	avltree->tree = ky_avltree_add_i(avltree->tree, value, avltree->value_len, key, avltree->key_len, avltree->cmp_fun);
}

void ky_avltree_mod(ky_avltree_t *avltree, void *key, void *value)
{
	avltree->tree = ky_avltree_mod_i(avltree->tree, value, avltree->value_len, key, avltree->key_len, avltree->cmp_fun);
}

void ky_avltree_del(ky_avltree_t *avltree, void *key)
{
	avltree->tree = ky_avltree_del_i(avltree->tree, key, avltree->key_len, avltree->value_len, avltree->cmp_fun);
}

