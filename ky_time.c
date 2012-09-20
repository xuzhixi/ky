#include <stdio.h>
#include<time.h>

#include <ky_time.h>

static void ky_get_localtime(struct tm *p)
{
	time_t timep;

	time(&timep);
	localtime_r(&timep, p); // 取得当地时间
}

char *ky_date_time(char *dtStr)
{
	struct tm p;

	ky_get_localtime( &p );
	sprintf(dtStr, "%d-%02d-%02d %02d:%02d:%02d", (1900+p.tm_year), (1+p.tm_mon), p.tm_mday, p.tm_hour, p.tm_min, p.tm_sec);

	return dtStr;
}

char *ky_now_time(char *tStr)
{
	struct tm p;

	ky_get_localtime( &p );
	sprintf(tStr, "%02d:%02d:%02d", p.tm_hour, p.tm_min, p.tm_sec);

	return tStr;
}
