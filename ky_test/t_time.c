#include <stdio.h>
#include <time.h>

#include <ky_time.h>


int main()
{
	//time_t timep;
	//struct tm p;
	//char dateStr[10];		// 记录当前日期
	//long date;
	//time(&timep);
	//localtime_r(&timep, &p);
	//sprintf(dateStr, "%d%02d%02d", (1900+p.tm_year), (1+p.tm_mon), p.tm_mday);
	//date = atol(dateStr);
	//printf("now: %ld\n", date);
	
	char dt[20];
	ky_time_t t;
	
	ky_localtime( &t );
	printf("%s\n", ky_now(dt, sizeof(dt), "yyyy-MM-dd hh:mm:ss"));
	printf("%s\n", ky_strftime(dt, sizeof(dt), "%Y-%m-%d %H:%M:%S"));
	printf("%d-%d-%d %d:%d:%d 星期%d\n", t.year, t.month, t.day, t.hour, t.minute, t.second, t.wday);

	return 0;
}

