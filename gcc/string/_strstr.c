/*====================================================================*
 *
 *   char *_strstr(char const *buffer, char const *string);
 *
 *   _string.h
 *
 *   This function returns a pointer to the first occurance of a substring
 *   within a string. NULL is returned if the substring does not occur or
 *   the string NULL. A NIL or NULL substring returns the string address.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../string/_string.h"

char *_strstr (register char const *buffer, register char const *string) 

{
	register char const *bp = buffer;
	register char const *sp = string;

#ifdef CMASSOC_SAFEMODE

	if (buffer == (char const *) (0)) 
	{
		return (buffer);
	}
	if (string == (char const *) (0)) 
	{
		return (buffer);
	}

#endif

	while ((*bp != (char) (0)) && (*sp != (char) (0))) 
	{
		if (*sp != *bp) 
		{
			bp = ++buffer;
			sp = string;
		}
		else 
		{
			bp++;
			sp++;
		}
	}
	return ((*sp == (char) (0))? (char *) (bp): (char *) (0));
}

