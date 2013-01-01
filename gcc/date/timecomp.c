/*====================================================================*
 *
 *   int timecomp (struct tm *thistime, struct tm *thattime);
 *
 *   compare the times stored in two tm structures and return either
 *   -1, 0 or 1 to indicated that the first time precedes, equals or 
 *   follows the second; ignore any stored date values;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef TIMECOMP_SOURCE
#define TIMECOMP_SOURCE

#include <time.h>

#include "../date/date.h"

int timecomp (struct tm *thistime, struct tm *thattime) 

{
	if (thistime->tm_hour > thattime->tm_hour) 
	{
		return (1);
	}
	if (thistime->tm_hour < thattime->tm_hour) 
	{
		return (-1);
	}
	if (thistime->tm_min > thattime->tm_min) 
	{
		return (1);
	}
	if (thistime->tm_min < thattime->tm_min) 
	{
		return (-1);
	}
	if (thistime->tm_sec > thattime->tm_sec) 
	{
		return (1);
	}
	if (thistime->tm_sec < thattime->tm_sec) 
	{
		return (-1);
	}
	return (0);
}


#endif

