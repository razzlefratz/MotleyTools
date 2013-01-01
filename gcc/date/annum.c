/*====================================================================*
 *
 *   int annum (struct tm * thisdate, struct tm * thatdate);
 *
 *   date.h
 *
 *   return the integral annual difference between two dates; account
 *   for relative month and year for each date; for example, dates in
 *   the same calendar year have no difference but dates separated by 
 *   more than 12 full months do have a difference; the difference is
 *   expressed as full calendar years;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ANNUM_SOURCE
#define ANNUM_SOURCE

#include <time.h>

#include "../date/date.h"

int annum (struct tm * thisdate, struct tm * thatdate) 

{
	int delta = thisdate->tm_year - thatdate->tm_year;
	if (thisdate->tm_mon > thatdate->tm_mon) 
	{
		return (delta);
	}
	else if (thisdate->tm_mon < thatdate->tm_mon) 
	{
		return (delta - 1);
	}
	else if (thisdate->tm_mday > thatdate->tm_mday) 
	{
		return (delta);
	}
	else if (thisdate->tm_mday < thatdate->tm_mday) 
	{
		return (delta - 1);
	}
	else if (thisdate->tm_hour > thatdate->tm_hour) 
	{
		return (delta);
	}
	else if (thisdate->tm_hour < thatdate->tm_hour) 
	{
		return (delta - 1);
	}
	else if (thisdate->tm_min > thatdate->tm_min) 
	{
		return (delta);
	}
	else if (thisdate->tm_min < thatdate->tm_min) 
	{
		return (delta - 1);
	}
	else if (thisdate->tm_sec > thatdate->tm_sec) 
	{
		return (delta);
	}
	else if (thisdate->tm_sec < thatdate->tm_sec) 
	{
		return (delta - 1);
	}
	return (delta);
}


#endif

