//===============================================
/**
 *  @file ky_mysql.c
 *
 *  @author XuZhiXi
 *  Email   932834199@qq.com or 932834199@163.com
 *
 *  Create datetime:  2012-10-17 08:12:29
 *  Last   modified:  2012-10-17 08:12:29
 *
 *  Description: 
 */
//================================================

#include <string.h>
#include <stdlib.h>
#include "ky_log.h"
#include "ky_string.h"
#include "ky_cmp.h"
#include "ky_mysql.h"

int g_ky_mysql_is_debug = 0;

ky_mysql_t *ky_mysql_new(unsigned int timeout)
{
	ky_mysql_t *my;

	my = (ky_mysql_t *)malloc( sizeof(ky_mysql_t) );
	my->db = mysql_init( NULL );
	my->res = NULL;
	my->field_map = ky_map_new( 0, 0, ky_cmp_str );
	my->is_debug = g_ky_mysql_is_debug;
	ky_mysql_options( my, MYSQL_OPT_CONNECT_TIMEOUT, (char *)&timeout );		// 设置 timeout 秒连接超时

	return my;
}

void ky_mysql_release(ky_mysql_t *my)
{
	// 清除结果集
	if ( my->res != NULL )
	{
		mysql_free_result( my->res );
	}
	// 关闭数据库连接
	mysql_close( my->db );
	ky_map_release( my->field_map );
	free( my );
}

int ky_mysql_options(ky_mysql_t *my, enum mysql_option option, const char *arg)
{
	if ( mysql_options( my->db, option, arg) == 0 )
	{
		return 1;
	}
	else
	{
		return 1;
	}
}

int ky_mysql_connect(ky_mysql_t *my, const char *host, const char *user, const char *pwd, const char *dbname, unsigned int port)
{
	if ( mysql_real_connect( my->db, host, user, pwd, dbname, port, 0, 0 ) != NULL )
	{
		return 1;
	}
	else
	{
		KY_LOG_ERROR("mysql#errno: %d errstr: %s", mysql_errno(my->db), mysql_error(my->db));
		return 0;
	}
}

int ky_mysql_execute(ky_mysql_t *my, const char *sql)
{
	if ( my->is_debug )
	{
		KY_LOG_INFO(sql);
	}

	if ( mysql_real_query( my->db , sql, strlen(sql) ) == 0 )
	{
		return 1;
	}
	else
	{
		KY_LOG_ERROR("mysql#errno: %d errstr: %s sql: %s", mysql_errno(my->db), mysql_error(my->db), sql);
		return 0;
	}
}

unsigned long ky_mysql_execute_id(ky_mysql_t *my, const char *sql)
{
	if ( ky_mysql_execute(my, sql) )
	{
		return mysql_insert_id( my->db );
	}
	else
	{
		return 0;
	}
}

static int ky_mysql_field_index(ky_mysql_t *my, const char *fieldName)
{
	ky_str_t *lowerFieldName = ky_str_new( fieldName );
	int *index;

	ky_str_tolower( lowerFieldName );
	index = ky_map_find( my->field_map, lowerFieldName->s );
	ky_str_release( lowerFieldName );
	if ( index != NULL )
	{
		return *index;
	}

	return -1;
}

int ky_mysql_select(ky_mysql_t *my, const char *sql)
{
	unsigned int fieldCount;
	MYSQL_FIELD *field;
	size_t valueLen;
	unsigned int i;

	if ( !ky_mysql_execute(my, sql) )
	{
		return 0;
	}

	// 如果结果集不为空，则先将其清空
	if ( my->res != NULL )
	{
		mysql_free_result( my->res );
	}
	// 保存新的结果集
	my->res = mysql_store_result( my->db );

	ky_map_clear( my->field_map );
	// 建立索引
	fieldCount = mysql_num_fields( my->res );
	field = mysql_fetch_fields( my->res );
	valueLen = sizeof(int);
	for (i=0; i<fieldCount; i++)
	{
		ky_map_addv( my->field_map, field[i].name, strlen(field[i].name)+1, &i, valueLen);
	}

	return 1;
}

int ky_mysql_next(ky_mysql_t *my)
{
	if ( my->res != NULL )	// 如果存在结果集
	{
		my->row = mysql_fetch_row( my->res );
		if ( my->row != NULL )	// 如果存在数据记录
		{
			return 1;
		}
	}

	return 0;
}

int ky_mysql_get_int(ky_mysql_t *my, const char *fieldName)
{
	int index;
	int value = -1;

	index = ky_mysql_field_index( my, fieldName );
	if ( index != -1 && my->row[index] )	// 如果找到索引且索引对应的值不为NULL
	{
		value = atoi( my->row[index] );
	}

	return value;
}

long ky_mysql_get_long(ky_mysql_t *my, const char *fieldName)
{
	int index;
	long value = -1;

	index = ky_mysql_field_index( my, fieldName );
	if ( index != -1 && my->row[index] )	// 如果找到索引且索引对应的值不为NULL
	{
		value = atol( my->row[index] );
	}

	return value;
}

char *ky_mysql_get_char(ky_mysql_t *my, const char *fieldName, char *dst, size_t dstLen)
{
	int index;

	index = ky_mysql_field_index( my, fieldName );
	if ( index != -1 && my->row[index] )	// 如果找到索引且索引对应的值不为NULL
	{
		ky_strcpy( dst, dstLen, my->row[index], strlen(my->row[index]) );
	}

	return dst;
}

unsigned long ky_mysql_affected_rows(ky_mysql_t *my)
{
	return mysql_affected_rows( my->db );
}

