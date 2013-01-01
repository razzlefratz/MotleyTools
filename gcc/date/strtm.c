/*====================================================================*
 *
 *   char const * strtm (struct tm * tm);
 *
 *   convert the time stored in a tm structure to a NUL terminated
 *   string and return a constant pointer to that string; the date
 *   format is intended to support sorting and searching;
 *
 *   2000-12-31 24:59:59
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRTM_SOURCE
#define STRTM_SOURCE

#include <time.h>

#include "../date/date.h"
#include "../tools/number.h"

char const * strtm (struct tm * tm) 

{
	static char buffer [LOGTIME_LEN];
	serial (&buffer [0], 4, '-', tm->tm_year + 1900);
	serial (&buffer [5], 2, '-', tm->tm_mon + 1);
	serial (&buffer [8], 2, ' ', tm->tm_mday);
	serial (&buffer [11], 2, ':', tm->tm_hour);
	serial (&buffer [14], 2, ':', tm->tm_min);
	serial (&buffer [17], 2, '\0', tm->tm_sec);
	return ((char const *)(buffer));
}


#endif

