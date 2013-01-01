/*====================================================================*
 *
 *   size_t strnchr(char const *literal, char const *charset);
 *
 *   strlib.h
 *
 *   scan a literal for characters in charset; return the number of
 *   times that any of the characters occur in string; return 0 when
 *   literal or charset are NULL or NIL; 
 *
 *   this function can be called to estimate how many fields exist
 *   within string when allocating memory for a string vector; see
 *   function strsplit() as one example where this might be useful;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRNCHR_SOURCE
#define STRNCHR_SOURCE

#include "../strlib/strlib.h"

size_t strnchr (register char const *literal, register char const *charset) 

{
	size_t count = 0;

#ifdef CMASSOC_SAFEMODE

	if (!literal) 
	{
		return (0);
	}
	if (!charset) 
	{
		return (0);
	}

#endif

	for (count = 0; *literal; literal++) 
	{
		char const *cp;
		for (cp = charset; *cp; ++cp) 
		{
			if (*cp == *literal) 
			{
				count++;
			}
		}
	}
	return (count);
}


#endif

