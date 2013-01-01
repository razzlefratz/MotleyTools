/*====================================================================*
 *
 *   size_t svfinal (char const *string, char const *vector[], size_t length, signed comp (char const *, char const *))
 *
 *   strlib.h
 *
 *   search a string vector of known length, back to front, for the
 *   given string; return the offset of the last match or the vector
 *   length if no match is found;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SVFINAL_SOURCE
#define SVFINAL_SOURCE

#include "../strlib/strlib.h"

size_t svfinal (char const *string, char const *vector [], size_t length, signed comp (char const *, char const *)) 

{
	size_t offset = length;

#ifdef CMASSOC_SAFEMODE

	if (string == (char const *) (0)) 
	{
		return (length);
	}
	if (vector == (char const **) (0)) 
	{
		return (length);
	}
	if (comp == (void *) (0)) 
	{
		return (length);
	}

#endif

	while (offset-- > 0) 
	{
		if (comp (string, vector [offset]) == 0) 
		{
			return (offset);
		}
	}
	return (length);
}


#endif

