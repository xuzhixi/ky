#include <stdio.h>
#include<time.h>

#include <ky_time.h>

char *ky_date_time(char *dtStr)
{
	time_t timep;
	struct tm p;

	time(&timep);
	localtime_r(&timep, &p); // 取得当地时间
	sprintf(dtStr, "%d-%d-%d %d:%d:%d", (1900+p.tm_year), (1+p.tm_mon), p.tm_mday, p.tm_hour, p.tm_min, p.tm_sec);

	return dtStr;
}

char *ky_now_time(char *tStr)
{
	time_t timep;
	struct tm p;

	time(&timep);
	localtime_r(&timep, &p); // 取得当地时间
	sprintf(tStr, "%d:%d:%d", p.tm_hour, p.tm_min, p.tm_sec);

	return tStr;
}
