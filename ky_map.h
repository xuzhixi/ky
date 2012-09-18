#ifndef _KY_MAP_H
#define _KY_MAP_H

#include <ky_rbtree.h>

#define ky_map_new( keyLen, valueLen, cmpFun)	ky_rbtree_new( (keyLen), (valueLen), (cmpFun) )
#define ky_map_clear( map )						ky_rbtree_clear( (map) )
#define ky_map_release( map )					ky_rbtree_release( (map) )
#define ky_map_is_null( map )					ky_rbtree_is_null( (map) )
#define ky_map_add( map, key, value )			ky_rbtree_add( (map), (key), (value) )
#define ky_map_mod( map, key, value )			ky_rbtree_mod( (map), (key), (value) )
#define ky_map_del( map, key )                  ky_rbtree_del( (map), (key) )
#define ky_map_find( map, key )                 ky_rbtree_find( (map), (key) )
#define ky_map_find_max( map )                  ky_rbtree_find_max( (map) )
#define ky_map_find_min( map )                  ky_rbtree_find_min( (map) )

typedef ky_rbtree_t ky_map_t;


#endif // _KY_MAP_H
