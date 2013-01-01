/*====================================================================*
 *
 *   char *daytime(time_t tm);
 *
 *   return the address of a custome formatted date and time string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef DAYTIME_SOURCE
#define DAYTIME_SOURCE

#include <time.h>

#include "../date/date.h"

char const *daytime (struct tm *tm) 

{
	static char datetime [DAYTIME_MAX];
	strftime (datetime, sizeof (datetime), DAYTIME, tm);
	return ((char const *) (datetime));
}

char const *rawtime (time_t time) 

{
	static char datetime [DAYTIME_MAX];
	strftime (datetime, sizeof (datetime), DAYTIME, localtime (&time));
	return ((char const *) (datetime));
}


#endif

