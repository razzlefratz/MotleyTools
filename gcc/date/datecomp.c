/*====================================================================*
 *
 *   int datecomp (struct tm *thisdate, struct tm *thatdate);
 *
 *   compare the dates stored in two tm structures and return either
 *   -1, 0 or 1 to indicated that the first date precedes, equals or 
 *   follows the second; ignore any stored time values;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef DATECOMP_SOURCE
#define DATECOMP_SOURCE

#include <time.h>

#include "../date/date.h"

int datecomp (struct tm *thisdate, struct tm *thatdate) 

{
	if (thisdate->tm_year > thatdate->tm_year) 
	{
		return (1);
	}
	if (thisdate->tm_year < thatdate->tm_year) 
	{
		return (-1);
	}
	if (thisdate->tm_mon > thatdate->tm_mon) 
	{
		return (1);
	}
	if (thisdate->tm_mon < thatdate->tm_mon) 
	{
		return (-1);
	}
	if (thisdate->tm_mday > thatdate->tm_mday) 
	{
		return (1);
	}
	if (thisdate->tm_mday < thatdate->tm_mday) 
	{
		return (-1);
	}
	return (0);
}


#endif

