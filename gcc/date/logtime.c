/*====================================================================*
 *
 *   char const * logtime(struct tm * tm);
 *
 *   date.h
 *
 *   return the address of a formatted date and time string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef LOGTIME_SOURCE
#define LOGTIME_SOURCE

#include <time.h>

#include "../date/date.h"

char const * logtime (struct tm * tm) 

{
	static char datetime [LOGTIME_LEN];
	strftime (datetime, sizeof (datetime), LOGTIME, tm);
	return ((char const *)(datetime));
}


#endif

