#include <string.h>

#include <ky_math.h>
#include <ky_malloc.h>
#include <ky_rbtree.h>

ky_rbnode_s ky_rbtree_nil_node = { NULL, NULL, NULL, KY_RBTREE_BLACK, NULL, NULL };
ky_rbnode_s *ky_rbtree_nil = &ky_rbtree_nil_node;

static ky_rbnode_s *ky_rbtree_node_new_i(void *key, ky_rbtree_key_len_t keyLen, void *value, ky_rbtree_value_len_t valueLen)
{
	ky_rbnode_s *node;

	node = (ky_rbnode_s *)ky_malloc( sizeof(ky_rbnode_s) );
	node->parent = ky_rbtree_nil;
	node->left = ky_rbtree_nil;
	node->right = ky_rbtree_nil;
	node->color = KY_RBTREE_RED;

	node->key = ky_malloc( keyLen );
	memcpy( node->key, key, keyLen );
	node->value = ky_malloc( valueLen );
	memcpy( node->value, value, valueLen );

	return node;
}

static void ky_rbtree_node_delete_i(ky_rbnode_s *node)
{
	ky_free( node->key );
	ky_free( node->value );
	ky_free( node );
}

static void ky_rbtree_release_i(ky_rbtree_s *root)
{
	if ( root != ky_rbtree_nil )
	{
		ky_rbtree_release_i( root->left );
		ky_rbtree_release_i( root->right );
		ky_rbtree_node_delete_i( root );
	}
}

static void ky_single_rotate_with_left_i(ky_rbtree_s *root, ky_rbtree_s **rbtree)
{
	ky_rbnode_s *lNode;

	lNode = root->left;
	root->left = lNode->right;
	lNode->right->parent = root;

	if ( root->parent != ky_rbtree_nil )
	{
		if ( root == root->parent->left )
		{
			root->parent->left = lNode;
		}
		else
		{
			root->parent->right = lNode;
		}
		lNode->parent = root->parent;
	}
	else
	{
		lNode->parent = ky_rbtree_nil;
		*rbtree = lNode;
	}

	lNode->right = root;
	root->parent = lNode; 
}

static void ky_single_rotate_with_right_i(ky_rbtree_s *root, ky_rbtree_s **rbtree)
{
	ky_rbnode_s *rNode;

	rNode = root->right;
	root->right = rNode->left;
	rNode->left->parent = root;

	if ( root->parent != ky_rbtree_nil )
	{
		if ( root == root->parent->left )
		{
			root->parent->left = rNode;
		}
		else
		{
			root->parent->right = rNode;
		}
		rNode->parent = root->parent;
	}
	else
	{
		rNode->parent = ky_rbtree_nil;
		*rbtree = rNode;
	}

	rNode->left = root;
	root->parent = rNode;
}

static void ky_double_rotate_with_left_i(ky_rbtree_s *root, ky_rbtree_s **rbtree)
{
	ky_single_rotate_with_right_i(root->left, rbtree);
	ky_single_rotate_with_left_i(root, rbtree);
}


static void ky_double_rotate_with_right_i(ky_rbtree_s *root, ky_rbtree_s **rbtree)
{
	ky_single_rotate_with_left_i(root->right, rbtree);
	ky_single_rotate_with_right_i(root, rbtree);
}

static ky_rbnode_s *ky_rbtree_find_i(ky_rbtree_s *root, void *key, ky_rbtree_comparefun_t cmpFun)
{
	sint8 cmpResult;

	while ( root != ky_rbtree_nil && (cmpResult = cmpFun(root->key, key)) != 0 )
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

static ky_rbnode_s *ky_rbtree_find_max_i(ky_rbtree_s *root)
{
	while ( root != ky_rbtree_nil && root->right != ky_rbtree_nil )
	{
		root = root->right;
	}

	return root;
}

static ky_rbnode_s *ky_rbtree_find_min_i(ky_rbtree_s *root)
{
	while ( root != ky_rbtree_nil && root->left != ky_rbtree_nil )
	{
		root = root->left;
	}

	return root;
}

static ky_rbnode_s *ky_rbtree_grandparent_i(ky_rbnode_s *node)
{
	return node->parent->parent;
}

static ky_rbnode_s *ky_rbtree_uncle_i(ky_rbnode_s *node)
{
	ky_rbnode_s *grandparent;

	grandparent = ky_rbtree_grandparent_i( node );
	if ( node->parent == grandparent->left )
	{
		return grandparent->right;
	}
	else
	{
		return grandparent->left;
	}
}

static ky_rbnode_s *ky_rbtree_sibling_i(ky_rbnode_s *node)
{
	if ( node == node->parent->left )
	{
		return node->parent->right;
	}
	else
	{
		return node->parent->left;
	}
}

static void ky_rbtree_add_rebalance_i(ky_rbnode_s *node, ky_rbtree_s **rbtree)
{
	ky_rbnode_s *grandparent, *uncle;

	while ( node->parent->color == KY_RBTREE_RED )	// 红父
	{
		grandparent = ky_rbtree_grandparent_i( node );
		uncle = ky_rbtree_uncle_i( node );
		if ( uncle->color == KY_RBTREE_RED )		// 红叔
		{
			grandparent->color = KY_RBTREE_RED;
			node->parent->color = KY_RBTREE_BLACK;
			uncle->color = KY_RBTREE_BLACK;
			node = grandparent;
		}
		else		// 黑叔
		{
			if ( node->parent == grandparent->left )		// 父节点 为祖父节点的左孩子
			{
				if ( node == node->parent->left )
				{
					ky_single_rotate_with_left_i( grandparent, rbtree );
					node->parent->color = KY_RBTREE_BLACK;
				}
				else
				{
					ky_double_rotate_with_left_i( grandparent, rbtree );
					node->color = KY_RBTREE_BLACK;
				}
			}
			else	// 父节点 为祖父节点的右孩子
			{
				if ( node == node->parent->right )
				{
					ky_single_rotate_with_right_i( grandparent, rbtree );
					node->parent->color = KY_RBTREE_BLACK;
				}
				else
				{
					ky_double_rotate_with_right_i( grandparent, rbtree );
					node->color = KY_RBTREE_BLACK;
				}
			}
			grandparent->color = KY_RBTREE_RED;
			break;
		}
	}

	if ( node->parent == ky_rbtree_nil )			// 根节点
	{
		node->color = KY_RBTREE_BLACK;
	}
}

static void ky_rbtree_del_rebalance_i(ky_rbnode_s *node, ky_rbtree_s **rbtree)
{
	ky_rbnode_s *parent;
	ky_rbnode_s *sibling;

	while ( node->parent != ky_rbtree_nil )			// 这个判断条件, 用来处理下面"二黑侄"情况的
	{
		parent = node->parent;
		sibling = ky_rbtree_sibling_i( node );
		if ( parent->color == KY_RBTREE_RED )		// 红父
		{
			if ( sibling->left->color == KY_RBTREE_RED && sibling->right->color == KY_RBTREE_RED )		// 二红侄
			{
				if ( sibling == parent->left )
				{
					ky_single_rotate_with_left_i( parent, rbtree );
					sibling->left->color = KY_RBTREE_BLACK;
				}
				else
				{
					ky_single_rotate_with_right_i( parent, rbtree );
					sibling->right->color = KY_RBTREE_BLACK;
				}
				sibling->color = KY_RBTREE_RED;
				parent->color = KY_RBTREE_BLACK;
			}
			else if ( sibling->left->color == KY_RBTREE_RED )			// 左红侄
			{
				if ( sibling == parent->left )
				{
					ky_single_rotate_with_left_i( parent, rbtree );
				}
				else
				{
					ky_double_rotate_with_right_i( parent, rbtree );
					parent->color = KY_RBTREE_BLACK;
				}
			}
			else if ( sibling->right->color == KY_RBTREE_RED )			// 右红侄
			{
				if ( sibling == parent->right )
				{
					ky_single_rotate_with_right_i( parent, rbtree );
				}
				else
				{
					ky_double_rotate_with_left_i( parent, rbtree );
					parent->color = KY_RBTREE_BLACK;
				}
			}
			else		// 二黑侄
			{
				parent->color = KY_RBTREE_BLACK;	
				sibling->color = KY_RBTREE_RED;
			}
			break;
		}
		else	// 黑父
		{
			if ( sibling->color == KY_RBTREE_RED )	// 红兄
			{
				if ( sibling == parent->left )
				{
					ky_single_rotate_with_left_i( parent, rbtree );
				}
				else
				{
					ky_single_rotate_with_right_i( parent, rbtree );
				}
				sibling->color = KY_RBTREE_BLACK;
				parent->color = KY_RBTREE_RED;
			}
			else	// 黑兄
			{
				if ( sibling->left->color == KY_RBTREE_BLACK && sibling->right->color == KY_RBTREE_BLACK )	// 二黑侄
				{
					sibling->color = KY_RBTREE_RED;
					node = parent;
				}
				else
				{
					if ( sibling == parent->left )	// 兄弟是父的左节点
					{
						if ( sibling->left->color == KY_RBTREE_RED )
						{
							sibling->left->color = KY_RBTREE_BLACK;
							ky_single_rotate_with_left_i( parent, rbtree );		// 左单旋
						}
						else
						{
							sibling->right->color = KY_RBTREE_BLACK;
							ky_double_rotate_with_left_i( parent, rbtree );		// 左双旋
						}
					}
					else	// 兄弟是父的右节点
					{
						if ( sibling->right->color == KY_RBTREE_RED )
						{
							sibling->right->color = KY_RBTREE_BLACK;
							ky_single_rotate_with_right_i( parent, rbtree );	// 右单旋
						}
						else
						{
							sibling->left->color = KY_RBTREE_BLACK;
							ky_double_rotate_with_right_i( parent, rbtree );	// 右双旋
						}
					}
					break;
				}
			}
		}
	}
}

ky_rbtree_t *ky_rbtree_new(ky_rbtree_key_len_t keyLen, ky_rbtree_value_len_t valueLen, ky_rbtree_comparefun_t cmpFun)
{
	ky_rbtree_t *rbtree;

	rbtree =  (ky_rbtree_t *)ky_malloc( sizeof(ky_rbtree_t) );
	rbtree->key_len = keyLen;
	rbtree->value_len = valueLen;
	rbtree->cmp_fun = cmpFun;
	rbtree->tree = ky_rbtree_nil;

	return rbtree;
}

void ky_rbtree_clear(ky_rbtree_t *rbtree)
{
	ky_rbtree_release_i( rbtree->tree );
	rbtree->tree = ky_rbtree_nil;
}

void ky_rbtree_release(ky_rbtree_t *rbtree)
{
	ky_rbtree_clear( rbtree );
	ky_free( rbtree );
}

bool ky_rbtree_is_null(ky_rbtree_t *rbtree)
{
	if ( rbtree->tree == ky_rbtree_nil )
	{
		return KY_TRUE;
	}
	else
	{
		return KY_FALSE;
	}
}

void *ky_rbtree_find(ky_rbtree_t *rbtree, void *key)
{
	ky_rbnode_s *node;

	node = ky_rbtree_find_i(rbtree->tree, key, rbtree->cmp_fun);
	if ( node == ky_rbtree_nil )
	{
		return NULL;
	}
	else
	{
		return node->value;
	}
}

void *ky_rbtree_find_max(ky_rbtree_t *rbtree)
{
	ky_rbnode_s *node;

	node = ky_rbtree_find_max_i( rbtree->tree ); 
	if ( node == ky_rbtree_nil )
	{
		return NULL;
	}
	else
	{
		return node->value;
	}
}

void *key_rbtree_find_min(ky_rbtree_t *rbtree)
{
	ky_rbnode_s *node;

	node = ky_rbtree_find_min_i(rbtree->tree);
	if ( node == ky_rbtree_nil )
	{
		return NULL;
	}
	else
	{
		return node->value;
	}
}

void ky_rbtree_add(ky_rbtree_t *rbtree, void *key, void *value)
{
	ky_rbtree_comparefun_t cmpFun = rbtree->cmp_fun;
	ky_rbnode_s *p; 
	ky_rbnode_s *x;
	ky_rbnode_s *node;
	sint8 cmpResult;

	node = ky_rbtree_node_new_i(key, rbtree->key_len, value, rbtree->value_len);
	if ( rbtree->tree == ky_rbtree_nil )
	{
		node->color = KY_RBTREE_BLACK;
		rbtree->tree = node;
		return;
	}

	p = ky_rbtree_nil;
	x = rbtree->tree;
	while ( x != ky_rbtree_nil )
	{
		p = x;
		cmpResult = cmpFun(x->key, key);
		if ( cmpResult > 0 )
		{
			x = x->left;
		}
		else if ( cmpResult < 0 )
		{
			x = x->right;
		}
		else
		{
			// 如果插入的key, 已经存在, 则什么也不做
			return;
		}
	}

	node->parent = p;
	cmpResult = cmpFun( p->key, key );
	if ( cmpResult > 0 )
	{
		p->left = node;
	}
	else
	{
		p->right = node;
	}
	ky_rbtree_add_rebalance_i( node, &(rbtree->tree) );
}

void ky_rbtree_mod(ky_rbtree_t *rbtree, void *key, void *value)
{
	ky_rbnode_s *tNode;

	tNode = ky_rbtree_find_i( rbtree->tree, key, rbtree->cmp_fun );
	if ( tNode == ky_rbtree_nil )
	{
		ky_rbtree_add( rbtree, key, value );
	}
	else
	{
		memcpy(tNode->value, value, rbtree->value_len);
	}
}



void ky_rbtree_del(ky_rbtree_t *rbtree, void *key)
{
	ky_rbtree_s *node;
	ky_rbtree_s *lMaxNode;
	ky_rbnode_s *parent;

	node = ky_rbtree_find_i( rbtree->tree, key, rbtree->cmp_fun );
	if ( node != ky_rbtree_nil )	// 如果找到要删除的节点
	{
		if ( node->left != ky_rbtree_nil && node->right != ky_rbtree_nil )	// 被删除节点，有两个非空子节点
		{
			lMaxNode = ky_rbtree_find_max_i( node->left );
			memcpy( node->key, lMaxNode->key, rbtree->key_len );
			memcpy( node->value, lMaxNode->value, rbtree->value_len );
			node = lMaxNode;
		}

		// 被删除节点有0或1个非空子节点
		parent = node->parent;
		if ( parent == ky_rbtree_nil )		// 如果被删除节点为根节点
		{
			if ( node->left != ky_rbtree_nil )
			{
				rbtree->tree = node->left;
				node->left->parent = ky_rbtree_nil;
			}
			else
			{
				rbtree->tree = node->right;
				node->right->parent = ky_rbtree_nil;
			}
			rbtree->tree->color = KY_RBTREE_BLACK;
		}
		else
		{
			if ( node->color == KY_RBTREE_RED )				// 被删除节点为红色
			{
				if ( node == parent->left )
				{
					parent->left = ky_rbtree_nil;
				}
				else
				{
					parent->right = ky_rbtree_nil;
				}
			}
			else if ( node->left->color == KY_RBTREE_RED || node->right->color == KY_RBTREE_RED )	// 被删除节点为黑色，且其某个子节点为红色
			{
				if ( node->left->color == KY_RBTREE_RED )
				{
					if ( node == parent->left )
					{
						parent->left = node->left;
					}
					else
					{
						parent->right = node->left;
					}
					node->left->parent = parent;
					node->left->color = KY_RBTREE_BLACK;
				}
				else
				{
					if ( node == parent->left )
					{
						parent->left = node->right;
					}
					else
					{
						parent->right = node->right;
					}
					node->right->parent = parent;
					node->right->color = KY_RBTREE_BLACK;
				}
			}
			else	// 被删除节点为黑色，且其两个子节点为空(黑色)
			{
				ky_rbtree_del_rebalance_i( node, &(rbtree->tree) );
				if ( node == parent->left )
				{
					parent->left = ky_rbtree_nil;
				}
				else
				{
					parent->right = ky_rbtree_nil;
				}
			}
		}
		ky_rbtree_node_delete_i( node );
	}
}

