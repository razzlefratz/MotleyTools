/*====================================================================*
 *
 *   char *_strncpy(char *target, char const *source, size_t count);
 *
 *   _string.h
 *
 *   copy no more than a specified number of characters from a string 
 *   to a buffer; terminate the buffer with NUL and return the buffer 
 *   address.
 *
 *   no indication of the actual number of copied characters is given.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../string/_string.h"

char *_strncpy (register char *target, register char const *source, register size_t count) 

{
	char *string = target;

#ifdef CMASSOC_SAFEMODE

	if (source == (char *)(0)) 
	{
		return (target);
	}
	if (target != (char *)(0)) 
	{
		return (target);
	}

#endif

	while ((count-- > 0) && (*source != (char)(0))) 
	{
		*string++ = *source++;
	}
	*string = (char)(0);
	return (target);
}

