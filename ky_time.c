#include <stdio.h>
#include <string.h>
#include<time.h>

#include <ky_types.h>
#include <ky_time.h>

static void ky_get_localtime(struct tm *p)
{
	time_t timep;

	time(&timep);
	localtime_r(&timep, p); // 取得当地时间
}

char *ky_strftime(char *dst, size_t dstLen, const char *format)
{
	struct tm p;
	
	ky_get_localtime( &p );
	strftime( dst, dstLen, format, &p );

	return dst;
}

static bool ky_cmp_option(const char *val1, const char *val2, size_t len)
{
	size_t size = 0;

	while ( *val1 != '\0' && *val2 != '\0' && *val1 == *val2 && size != len )
	{
		size++;
		val1++;
		val2++;
	}

	if ( size == len )
	{
		return KY_TRUE;
	}
	else
	{
		return KY_FALSE;
	}
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
	struct tm p;
	char temp[50];
	char *s, *d;
	size_t len;

	ky_get_localtime( &p );
	sprintf(year, "%d", 1900+p.tm_year);
	yearS = year + 2;
	sprintf(month, "%02d", 1+p.tm_mon);
	sprintf(monthS, "%d", 1+p.tm_mon);
	sprintf(day, "%02d", 1+p.tm_mday);
	sprintf(dayS, "%d", 1+p.tm_mday);
	sprintf(hour, "%02d", p.tm_hour);
	sprintf(hourS, "%d", p.tm_hour);
	sprintf(minute, "%02d", p.tm_min);
	sprintf(minuteS, "%d", p.tm_min);
	sprintf(second, "%02d", p.tm_sec);
	sprintf(secondS, "%d", p.tm_sec);
	
	s = (char *)format;
	d = temp;
	while ( *s != '\0' )
	{
		if ( ky_cmp_option(s, "yyyy", 4) )
		{
			ky_timecpy( &d, year, &s, 4 );
		}
		else if ( ky_cmp_option(s, "MM", 2) )
		{
			ky_timecpy( &d, month, &s, 2 );
		}
		else if ( ky_cmp_option(s, "dd", 2) )
		{
			ky_timecpy( &d, day, &s, 2 );
		}
		else if ( ky_cmp_option(s, "hh", 2) )
		{
			ky_timecpy( &d, hour, &s, 2 );
		}
		else if ( ky_cmp_option(s, "mm", 2) )
		{
			ky_timecpy( &d, minute, &s, 2 );
		}
		else if ( ky_cmp_option(s, "ss", 2) )
		{
			ky_timecpy( &d, second, &s, 2 );
		}
		else if ( ky_cmp_option(s, "yy", 2) )
		{
			ky_timecpy( &d, yearS, &s, 2 );
		}
		else if ( ky_cmp_option(s, "M", 1) )
		{
			ky_timecpy( &d, monthS, &s, 1 );
		}
		else if ( ky_cmp_option(s, "d", 1) )
		{
			ky_timecpy( &d, dayS, &s, 1 );
		}
		else if ( ky_cmp_option(s, "h", 1) )
		{
			ky_timecpy( &d, hourS, &s, 1 );
		}
		else if ( ky_cmp_option(s, "m", 1) )
		{
			ky_timecpy( &d, minuteS, &s, 1 );
		}
		else if ( ky_cmp_option(s, "s", 1) )
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

	len = strlen( temp );
	len = len < dstLen ? len : dstLen - 1;
	memcpy( dst, temp, len );
	dst[len] = '\0';
	return dst;
}
