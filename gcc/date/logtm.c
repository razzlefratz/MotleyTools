/*====================================================================*
 *
 *   char const * logtm (struct tm * tm);
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

#ifndef LOGTM_SOURCE
#define LOGTM_SOURCE

#include <time.h>
#include <stdio.h>

#include "../date/date.h"

char const * logtm (struct tm * tm) 

{
	static char buffer [LOGTIME_LEN+1];
	char *sp = buffer;
	sp += snprintf (sp, buffer + sizeof (buffer) - sp, "%04d-", tm->tm_year + 1900);
	sp += snprintf (sp, buffer + sizeof (buffer) - sp, "%02d-", tm->tm_mon + 1);
	sp += snprintf (sp, buffer + sizeof (buffer) - sp, "%02d ", tm->tm_mday);
	sp += snprintf (sp, buffer + sizeof (buffer) - sp, "%02d:", tm->tm_hour);
	sp += snprintf (sp, buffer + sizeof (buffer) - sp, "%02d:", tm->tm_min);
	sp += snprintf (sp, buffer + sizeof (buffer) - sp, "%02d ", tm->tm_sec);
	return ((char const *) (buffer));
}


#endif

