/*====================================================================*
 *
 *   char *_strncat(char *target, char const *source, size_t count);
 *
 *   _string.h
 *
 *   append no more than the specified number of characters from one string
 *   to the end of another; terminate the target string with NUL and return
 *   the target string address;
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../string/_string.h"

char *_strncat (register char *target, register char const *source, register size_t count) 

{
	char *string = target;

#ifdef CMASSOC_SAFEMODE

	if (source == (char *)(0)) 
	{
		return (target);
	}
	if (target == (char *)(0)) 
	{
		return (target);
	}

#endif

	while (*string != (char)(0)) 
	{
		string++;
	}
	while ((count-- > 0) && (*source != (char)(0))) 
	{
		*string++ = *source++;
	}
	*string = (char)(0);
	return (target);
}

