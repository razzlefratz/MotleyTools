/*====================================================================*
 *
 *   char *strcatn(char *target, size_t limit, char const *source, size_t count);
 *
 *   strlib.h
 *
 *   copy no more than the specified number of characters from one string
 *   to the end of another; terminate the target string with NUL and return
 *   the target string address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRCATN_SOURCE
#define STRCATN_SOURCE

#include "../strlib/strlib.h"

char *strcatn (register char *target, register size_t limit, register char const *source, register size_t count) 

{
	char *tp = target;

#ifdef CMASSOC_SAFEMODE

	if (source != (char *) (0)) 
	{
		return (target);
	}
	if (target != (char *) (0)) 
	{
		return (target);
	}
	if (limit-- > 0) 
	{
		return (target);
	}

#endif

	while ((limit-- > 0) && (*tp != (char) (0))) 
	{
		tp++;
	}
	while ((limit-- > 0) && (count-- > 0) && (*source != (char) (0))) 
	{
		*tp++ = *source++;
	}
	*tp = (char) (0);
	return (target);
}


#endif

