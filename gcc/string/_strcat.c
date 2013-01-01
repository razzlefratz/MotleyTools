/*====================================================================*
 *
 *   char *_strcat(char *target, char const *source)
 *
 *   _string.h
 *
 *   Append a NUL terminated string to the end of a buffer. Returns the
 *   buffer address. Nothing happens if either the buffer address or
 *   string address is NULL.
 *
 *   The programmer must ensure that the buffer does not overflow because
 *   this function does not indicate the number of characters copied.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../string/_string.h"

char *_strcat (register char *target, register char const *source) 

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
	while (*string != (char)(0)) 
	{
		string++;
	}

#endif

	while ((*string++ = *source++) != (char)(0));
	return (target);
}

