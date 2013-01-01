/*====================================================================*
 *
 *   char *_strrev(char *string);
 *
 *   _string.h
 *
 *   reverse the order of characters in a string and return the string
 *   address;
 *
 *   this function can be used to simplify numeric string conversion (see
 *   itoa()) and speed email address comparison;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../string/_string.h"

char *_strrev (register char *string) 

{
	register char *first = string;
	register char *final = string;
	register char c;

#ifdef CMASSOC_SAFEMODE

	if (string == (char *)(0)) 
	{
		return (string);
	}

#endif

	while (*final != (char)(0)) 
	{
		final++;
	}
	while (first < final) 
	{
		c = *--final;
		*final = *first;
		*first++ = c;
	}
	return (string);
}

