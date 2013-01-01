/*====================================================================*
 *
 *   char *_strchr(char const *string, int c);
 *
 *   _string.h
 *
 *   search a string for the left-most occurance of a character; 
 *   return the character address if present; return NULL if not;
 *
 *   this function returns the address of the string terminator 
 *   when c is NUL;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../string/_string.h"

char *_strchr (register char const *string, register int c) 

{

#ifdef CMASSOC_SAFEMODE

	if (string == (char *) (0)) 
	{
		return (string);
	}

#endif

	while (*string != (char) (c)) 
	{
		if (*string++ == (char) (0)) 
		{
			return ((char *) (0));
		}
	}
	return ((char *)(string));
}

