//===============================================
/**
 *  @file ky_map.h
 *
 *  @author XuZhiXi
 *  Email   932834199@qq.com or 932834199@163.com
 *
 *  Create datetime:  2012-10-17 08:11:58
 *  Last   modified:  2012-10-17 08:11:58
 *
 *  Description: 
 */
//================================================

#ifndef _KY_MAP_H
#define _KY_MAP_H

#include "ky_avltree.h"
#include "ky_rbtree.h"

#ifndef _USE_AVLTREE
#define ky_map_new( keyLen, valueLen, cmpFun )	ky_rbtree_new( (keyLen), (valueLen), (cmpFun) )
#define ky_map_clear( map )						ky_rbtree_clear( (map) )
#define ky_map_release( map )					ky_rbtree_release( (map) )
#define ky_map_is_null( map )					ky_rbtree_is_null( (map) )
#define ky_map_add( map, key, value )			ky_rbtree_add( (map), (key), (value) )
#define ky_map_addv( map, key, key_len, value, value_len )	ky_rbtree_addv( (map), (key), (key_len), (value), (value_len) )
#define ky_map_mod( map, key, value )			ky_rbtree_mod( (map), (key), (value) )
#define ky_map_modv( map, key, key_len, value, value_len )	ky_rbtree_modv( (map), (key), (key_len), (value), (value_len) )
#define ky_map_del( map, key )                  ky_rbtree_del( (map), (key) )
#define ky_map_find( map, key )                 ky_rbtree_find( (map), (key) )
#define ky_map_find_max( map )                  ky_rbtree_find_max( (map) )
#define ky_map_find_min( map )                  ky_rbtree_find_min( (map) )
typedef ky_rbtree_t ky_map_t;
#else
#define ky_map_new( keyLen, valueLen, cmpFun )	ky_avltree_new( (keyLen), (valueLen), (cmpFun) )
#define ky_map_clear( map )						ky_avltree_clear( (map) )
#define ky_map_release( map )					ky_avltree_release( (map) )
#define ky_map_is_null( map )					ky_avltree_is_null( (map) )
#define ky_map_add( map, key, value )			ky_avltree_add( (map), (key), (value) )
#define ky_map_addv( map, key, key_len, value, value_len )	ky_avltree_addv( (map), (key), (key_len), (value), (value_len) )
#define ky_map_mod( map, key, value )			ky_avltree_mod( (map), (key), (value) )
#define ky_map_modv( map, key, key_len, value, value_len )	ky_avltree_modv( (map), (key), (key_len), (value), (value_len) )
#define ky_map_del( map, key )                  ky_avltree_del( (map), (key) )
#define ky_map_find( map, key )                 ky_avltree_find( (map), (key) )
#define ky_map_find_max( map )                  ky_avltree_find_max( (map) )
#define ky_map_find_min( map )                  ky_avltree_find_min( (map) )
typedef ky_avltree_t ky_map_t;
#endif

#endif // _KY_MAP_H
