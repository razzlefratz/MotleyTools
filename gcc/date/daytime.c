/*====================================================================*
 *
 *   char const * daytime(struct tm * tm);
 *
 *   date.h
 *
 *   return the address of a custom formatted date and time string;
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

char const * daytime (struct tm * tm) 

{
	static char datetime [DAYTIME_LEN];
	strftime (datetime, sizeof (datetime), DAYTIME, tm);
	return ((char const *)(datetime));
}


#endif

