/*====================================================================*
 *
 *   time_t weekdate (time_t time, unsigned weekday);
 *
 *   convert the time in seconds since the epoch to the same time of 
 *   day on the most recent weekday specified; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef WEEKDATE_SOURCE
#define WEEKDATE_SOURCE

#include <time.h>

#include "../date/date.h"

time_t weekdate (time_t time, unsigned weekday) 

{
	struct tm tm = *localtime (&time);
	time -= tm.tm_wday * 86400;
	time += weekday * 86400;
	return (time);
}


#endif

