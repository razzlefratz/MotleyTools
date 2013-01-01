/*====================================================================*
 *
 *   time_t workdate (time_t time);
 *
 *   return the nearest working day for a given a date; return the  
 *   date of the previous friday if time falls on a saturday or the 
 *   date of the following monday if time falls on a sunday; 
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef WORKDATE_SOURCE
#define WORKDATE_SOURCE

#include <time.h>

#include "../date/date.h"

time_t workdate (time_t time) 

{
	struct tm tm = *localtime (&time);
	if (tm.tm_wday == 0) 
	{
		tm.tm_mday--;
	}
	if (tm.tm_wday == 6) 
	{
		tm.tm_mday++;
	}
	time = mktime (&tm);
	return (time);
}


#endif

