/*====================================================================*
 *
 *   time_t fridate (time_t time);
 *
 *   date.h
 *
 *   return the the date of the following monday when time falls on 
 *   a saturday or a sunday; 
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FRIDATE_SOURCE
#define FRIDATE_SOURCE

#include <time.h>

#include "../date/date.h"

time_t fridate (time_t time) 

{
	struct tm tm = *localtime (&time);
	if (tm.tm_wday == 0) 
	{
		tm.tm_mday--;
		tm.tm_mday--;
	}
	if (tm.tm_wday == 6) 
	{
		tm.tm_mday--;
	}
	time = mktime (&tm);
	return (time);
}


#endif

