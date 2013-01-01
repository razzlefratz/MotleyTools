/*====================================================================*
 *
 *   size_t strmerge (char buffer[], size_t length, char const *vector[], signed c);
 *
 *   strlib.h
 *
 *   create one string from vector strings; separate each string 
 *   with one character; preserve the vector; rewrite the buffer;
 *   return the resulting string length;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRMERGE_SOURCE
#define STRMERGE_SOURCE

#include "../strlib/strlib.h"

size_t strmerge (char buffer [], size_t length, char const * vector [], signed c) 

{
	register char *cp = buffer;

#ifdef CMASSOC_SAFEMODE

	if (vector == (char const **) (0)) 
	{
		return (0);
	}
	if (buffer == (char *) (0)) 
	{
		return (0);
	}

#endif

	if (length-- > 1) 
	{
		while (*vector != (char *) (0)) 
		{
			char const *sp = *vector++;
			while (*sp != (char) (0)) 
			{
				if (length-- > 1) 
				{
					*cp++ = *sp++;
				}
			}
			if (length-- > 1) 
			{
				*cp++ = c;
			}
		}
		*cp = (char) (0);
	}
	return (cp - buffer);
}


#endif

