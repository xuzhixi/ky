//===============================================
/**
 *  @file ky_sqlite3.c
 *
 *  @author XuZhiXi
 *  Email   932834199@qq.com or 932834199@163.com
 *
 *  Create datetime:  2012-10-17 08:13:27
 *  Last   modified:  2012-10-17 08:13:27
 *
 *  Description: 
 */
//================================================

#include <stdio.h>
#include <sqlite3.h>
#include "ky_log.h"

//int main()
//{
//	sqlite3 *db = NULL;
//	if ( sqlite3_open("ky_test/pwas.db", &db) == SQLITE_OK )
//	{
//		printf("OK!\n");
//		if ( db != NULL )
//		{
//			sqlite3_close(db);
//		}
//	}
//	else
//	{
//		KY_LOG_ERROR("sqlite3#errno: %d errstr: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
//	}
//
//	return 0;
//}
