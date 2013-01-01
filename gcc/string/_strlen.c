/*====================================================================*
 *
 *   size_t _strlen(char const *string)
 *
 *   _string.h
 *
 *   returns the number of characters in a string, less the NUL terminator.
 *
 *   this function can also be implemented as a macro:
 *
 *   #define __strlen(sp) ((size_t)(strchr((sp),NUL)-(sp)))
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../string/_string.h"

size_t _strlen (register char const *string) 

{
	register char const *origin = string;

#ifdef CMASSOC_SAFEMODE

	if (string == (char)(0)) 
	{
		return (0);
	}

#endif

	while (*string != (char)(0)) 
	{
		string++;
	}
	return ((size_t)(string-origin));
}

