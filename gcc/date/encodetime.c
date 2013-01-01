/*====================================================================*
 *
 *   char *encodetime(char buffer[], size_t length, unsigned c, struct tm *tm)
 *
 *   encode buffer with the date and time specified in a tm structure; 
 *   terminate the encoded string with character c;  return the address
 *   of the next unencoded character in buffer; the format is:
 *
 *      2000-12-31 24:59:59(c)
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ENCODETIME_SOURCE
#define ENCODETIME_SOURCE

#include <time.h>

#include "../tools/number.h"
#include "../date/date.h"

char *encodetime (char buffer [], size_t length, unsigned c, struct tm *tm) 

{
	if (!buffer || (length < 20)) 
	{
		return (buffer);
	}
	serial (&buffer [0], 4, '-', tm->tm_year+1900);
	serial (&buffer [5], 2, '-', tm->tm_mon+1);
	serial (&buffer [8], 2, ' ', tm->tm_mday);
	serial (&buffer [11], 2, ':', tm->tm_hour);
	serial (&buffer [14], 2, ':', tm->tm_min);
	serial (&buffer [17], 2, c, tm->tm_sec);
	return (&buffer [20]);
}


#endif

