//===============================================
/**
 *  @file ky_time.c
 *
 *  @author XuZhiXi
 *  Email   zhixi.xu@qq.com or 932834199@163.com
 *
 *  Create datetime:  2012-10-17 08:15:23
 *  Last   modified:  2012-10-17 08:15:23
 *
 *  Description: 
 */
//================================================

#include <stdio.h>
#include <string.h>
#include "ky_time.h"

#ifdef __WIN32
#include <windows.h>
#endif


void ky_localtime(ky_time_t *t)
{
#ifdef __linux
	time_t timep;
	struct tm p;

	time(&timep);
	localtime_r(&timep, &p);
	t->year     = 1900+p.tm_year;
	t->month    = 1+p.tm_mon;
	t->day      = p.tm_mday;
	t->hour     = p.tm_hour;
	t->minute   = p.tm_min;
	t->second   = p.tm_sec;
	t->wday     = p.tm_wday;
#endif
#ifdef __WIN32
	SYSTEMTIME sys;

	GetLocalTime( &sys );
	t->year		= sys.wYear;
	t->month	= sys.wMonth;
	t->day		= sys.wDay;
	t->hour		= sys.wHour;
	t->minute	= sys.wMinute;
	t->second	= sys.wSecond;
	t->wday		= sys.wDayOfWeek;
	t->milli_second = sys.wMilliseconds;
#endif
}

void ky_current_tm(struct tm *p)
{
#ifdef __linux
	time_t timep;

	time(&timep);
	localtime_r(&timep, p);
#endif
#ifdef __WIN32
	ky_time_t t;

	ky_localtime( &t );
	p->tm_year	= t.year - 1900;
	p->tm_mon	= t.month - 1;
	p->tm_mday	= t.day;
	p->tm_hour	= t.hour;
	p->tm_min	= t.minute;
	p->tm_sec	= t.second;
	p->tm_wday	= t.wday;
	p->tm_yday	= 1;
	p->tm_isdst	= 1;
#endif
}

char *ky_strftime(char *dst, size_t dstLen, const char *format)
{
	struct tm p;
	
	ky_current_tm( &p );
	strftime( dst, dstLen, format, &p );

	return dst;
}

static void ky_timecpy(char **dst, char *time, char **opt, size_t optLen)
{
	size_t timeLen;

	timeLen = strlen(time);
	memcpy( *dst, time, timeLen);
	*opt += optLen;
	*dst += timeLen;
}

char *ky_now(char *dst, size_t dstLen, const char *format)
{
	char year[5];
	char *yearS;
	char month[3];
	char monthS[3];
	char day[3];
	char dayS[3];
	char hour[3];
	char hourS[3];
	char minute[3];
	char minuteS[3];
	char second[3];
	char secondS[3];
	ky_time_t t;
	char temp[50];
	char *s, *d;

	ky_localtime( &t );
	sprintf(year,    "%d",   t.year);
	yearS = year + 2;
	sprintf(month,   "%02d", t.month);
	sprintf(monthS,  "%d",   t.month);
	sprintf(day,	 "%02d", t.day);
	sprintf(dayS,    "%d",   t.day);
	sprintf(hour,    "%02d", t.hour);
	sprintf(hourS,   "%d",   t.hour);
	sprintf(minute,  "%02d", t.minute);
	sprintf(minuteS, "%d",   t.minute);
	sprintf(second,  "%02d", t.second);
	sprintf(secondS, "%d",   t.second);
	
	s = (char *)format;
	d = temp;
	while ( *s != '\0' )
	{
		if ( memcmp(s, "yyyy", 4) == 0 )
		{
			ky_timecpy( &d, year, &s, 4 );
		}
		else if ( memcmp(s, "MM", 2) == 0 )
		{
			ky_timecpy( &d, month, &s, 2 );
		}
		else if ( memcmp(s, "dd", 2) == 0 )
		{
			ky_timecpy( &d, day, &s, 2 );
		}
		else if ( memcmp(s, "hh", 2) == 0 )
		{
			ky_timecpy( &d, hour, &s, 2 );
		}
		else if ( memcmp(s, "mm", 2) == 0 )
		{
			ky_timecpy( &d, minute, &s, 2 );
		}
		else if ( memcmp(s, "ss", 2) == 0 )
		{
			ky_timecpy( &d, second, &s, 2 );
		}
		else if ( memcmp(s, "yy", 2) == 0 )
		{
			ky_timecpy( &d, yearS, &s, 2 );
		}
		else if ( memcmp(s, "M", 1) == 0 )
		{
			ky_timecpy( &d, monthS, &s, 1 );
		}
		else if ( memcmp(s, "d", 1) == 0 )
		{
			ky_timecpy( &d, dayS, &s, 1 );
		}
		else if ( memcmp(s, "h", 1) == 0 )
		{
			ky_timecpy( &d, hourS, &s, 1 );
		}
		else if ( memcmp(s, "m", 1) == 0 )
		{
			ky_timecpy( &d, minuteS, &s, 1 );
		}
		else if ( memcmp(s, "s", 1) == 0 )
		{
			ky_timecpy( &d, secondS, &s, 1 );
		}
		else
		{
			*d = *s;
			s++;
			d++;
		}
	}
	*d = '\0';

	snprintf(dst, dstLen, temp);
	return dst;
}
