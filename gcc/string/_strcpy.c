/*====================================================================*
 *
 *   char *_strcpy(char *target, char const *source);
 *
 *   _string.h
 *
 *   copy one NUL terminated string to another; return the target string
 *   address; do nothing if either string address is NULL;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../string/_string.h"
#include "../stdlib/_memory.h"

char *_strcpy (register char *target, register char const *source) 

{
	char *string = target;

#ifdef CMASSOC_SAFEMODE

	if (source == target) 
	{
		return (target);
	}
	if (source == (char *)(0)) 
	{
		return (target);
	}
	if (target == (char *)(0)) 
	{
		return (target);
	}

#endif

	while ((*string++ = *source++) != (char)(0));
	return (target);
}

