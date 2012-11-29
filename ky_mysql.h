//===============================================
/**
 *  @file ky_mysql.h
 *
 *  @author XuZhiXi
 *  Email   zhixi.xu@qq.com or 932834199@163.com
 *
 *  Create datetime:  2012-10-17 08:12:26
 *  Last   modified:  2012-10-17 08:12:26
 *
 *  Description: 
 */
//================================================

#ifndef _KY_MYSQL_H
#define _KY_MYSQL_H

#include <mysql/mysql.h>
#include "ky_map.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct ky_mysql_t {
	MYSQL *db;						///< 数据库连接
	MYSQL_RES *res;					///< 保存查询的结果集
	ky_map_t *field_map;			///< 保存字段与索引的映射对
	MYSQL_ROW row;					///< 保存一行数据
	int is_debug;					///< 如果设置为非0, 则会打印每句执行的SQL语句
}ky_mysql_t;

extern int g_ky_mysql_is_debug;	///< 用于调节ky_mysql_t的is_debug属性,默认值为0

extern ky_mysql_t *ky_mysql_new(unsigned int timeout);
extern void ky_mysql_release(ky_mysql_t *my);
extern int ky_mysql_options(ky_mysql_t *my, enum mysql_option option, const char *arg);
extern int ky_mysql_connect(ky_mysql_t *my, const char *host, const char *user, const char *pwd, const char *dbname, unsigned int port);
extern int ky_mysql_execute(ky_mysql_t *my, const char *sql);
extern unsigned long ky_mysql_execute_id(ky_mysql_t *my, const char *sql);
extern int ky_mysql_select(ky_mysql_t *my, const char *sql);
extern int ky_mysql_next(ky_mysql_t *my);
extern int ky_mysql_get_int(ky_mysql_t *my, const char *fieldName);
extern long ky_mysql_get_long(ky_mysql_t *my, const char *fieldName);
extern char *ky_mysql_get_char(ky_mysql_t *my, const char *fieldName, char *dst, size_t dstLen);
extern unsigned long ky_mysql_affected_rows(ky_mysql_t *my);


#ifdef __cplusplus
}
#endif

#endif // _KY_MYSQL_H
