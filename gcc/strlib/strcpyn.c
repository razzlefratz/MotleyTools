/*====================================================================*
 *
 *   char *strcpyn(char *target, size_t limit, char const *source, size_t count);
 *
 *   strlib.h
 *
 *   copy no more than the specified number of characters from one string
 *   to another; terminate the target string and return the target string
 *   address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRCPYN_SOURCE
#define STRCPYN_SOURCE

#include "../strlib/strlib.h"

char *strcpyn (register char *target, size_t limit, register char const *source, register size_t count) 

{
	char *tp;

#ifdef CMASSOC_SAFEMODE

	if (target == (char *) (0)) 
	{
		return (target);
	}
	if (source == (char const) (0)) 
	{
		return (target);
	}

#endif

	for (tp = target; (limit-- > 0) && (count-- > 0) && (*source != (char) (0)); *tp++ = *source++);
	*tp = (char) (0);
	return (target);
}


#endif

