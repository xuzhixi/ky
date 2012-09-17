#include <string.h>
#include <stdlib.h>

#include <ky_malloc.h>
#include <ky_linklist.h>

static ky_linklist_s *ky_linklist_node_init_i(void *value, ky_linklist_value_len_t valueLen)
{
	ky_linklist_s *node;

	node = ky_malloc( sizeof(ky_linklist_s) );
	node->value = ky_malloc( valueLen );
	memcpy( node->value, value, valueLen );
	node->next = NULL;

	return node;
}

static void ky_linklist_node_release_i(ky_linklist_s *node)
{
	ky_free( node->value );
	ky_free( node );
}

ky_linklist_t *ky_linklist_new(ky_linklist_value_len_t valueLen, ky_linklist_comparefun_t cmpFun)
{
	ky_linklist_t *linklist;

	linklist = ky_malloc( sizeof(ky_linklist_t) );
	linklist->value_len = valueLen;
	linklist->cmp_fun = cmpFun;
	linklist->head = NULL;
	linklist->tail = NULL;

	return linklist;
}

void ky_linklist_clear(ky_linklist_t *linklist)
{
	ky_linklist_s *p;
	ky_linklist_s *t;	

	p = t = linklist->head;
	if ( p != NULL )
	{
		while ( p->next != NULL )
		{
			t = p;
			p = p->next;
			ky_linklist_node_release_i( t );
		}
		ky_linklist_node_release_i( p );
	}
	linklist->head = linklist->tail = NULL;
}

void ky_linklist_release(ky_linklist_t *linklist)
{
	ky_linklist_clear( linklist );
	ky_free( linklist );
}

bool ky_linklist_is_null(ky_linklist_t *linklist)
{
	if ( linklist->head == NULL )
	{
		return KY_TRUE;
	}
	else
	{
		return KY_FALSE;
	}
}

void *ky_linklist_find(ky_linklist_t *linklist, void *value)
{
	ky_linklist_s *p;

	p = linklist->head;
	while ( p != NULL )
	{
		if ( linklist->cmp_fun(p->value, value) == 0 )
		{
			return p;
		}
		p = p->next;
	}

	return NULL;
}
	
void ky_linklist_add(ky_linklist_t *linklist, void *value)
{
	ky_linklist_s *node;

	node = ky_linklist_node_init_i( value, linklist->value_len );
	if ( linklist->tail == NULL )
	{
		linklist->head = linklist->tail = node;
	}
	else
	{
		linklist->tail->next = node;
		linklist->tail = node;
	}
}

void ky_linklist_insert(ky_linklist_t *linklist, void *value, void *insertValue)
{
	ky_linklist_s *node;
	ky_linklist_s *p, *t;
	sint8 cmpResult;

	node = ky_linklist_node_init_i( insertValue, linklist->value_len );

	t = p = linklist->head;
	if ( t == NULL )
	{
		linklist->head = linklist->tail = node;
	}
	else
	{
		cmpResult = linklist->cmp_fun(t->value, value);
		while ( cmpResult != 0 && t->next != NULL )
		{
			p = t;
			t = t->next;
			cmpResult = linklist->cmp_fun(t->value, value);
		}
		if ( cmpResult != 0 )
		{
			linklist->tail->next = node;	// 没有找到插入的位置，则在最后插入
		}
		else
		{
			if ( p != t )
			{
				node->next = p->next;
				p->next = node;
			}
			else
			{
				node->next = linklist->head;
				linklist->head = node;
			}
		}
	}
}

void ky_linklist_mod(ky_linklist_t *linklist, void *value)
{
	ky_linklist_s *p;

	p = ky_linklist_find( linklist, value );
	if ( p != NULL )
	{
		// 找到则修改
		memcpy( p->value, value, linklist->value_len );
	}
	else
	{
		// 没有找到则插入
		ky_linklist_add( linklist, value );
	}
}

void ky_linklist_del(ky_linklist_t *linklist, void *value)
{
	ky_linklist_s *p, *t;
	sint8 cmpResult; 

	p = t = linklist->head;
	if ( t != NULL )
	{
		cmpResult = linklist->cmp_fun(t->value, value);
		while ( cmpResult != 0 && t->next != NULL )
		{
			p = t;
			t = t->next;
			cmpResult = linklist->cmp_fun(t->value, value);
		}
		if ( cmpResult == 0 )
		{
			if ( t != linklist->head )
			{
				p->next = t->next;
			}
			else
			{
				linklist->head = linklist->tail = t->next;
			}
			ky_linklist_node_release_i( t );
		}
	}
}

ky_linklist_iter_t *ky_linklist_iter(ky_linklist_t *linklist)
{
	return linklist->head;
}

ky_linklist_iter_t *ky_linklist_iter_next(ky_linklist_iter_t *iter)
{
	return iter->next;
}

void *ky_linklist_iter_value(ky_linklist_iter_t *iter)
{
	return iter->value;
}

