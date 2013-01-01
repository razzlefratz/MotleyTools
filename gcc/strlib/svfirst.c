/*====================================================================*
 *
 *   size_t svfirst(char const * string, char const * vector[], size_t length, signed comp (char const *, char const *))
 *
 *   strlib.h
 *
 *   search a string vector of known length, front to back, for a 
 *   given string; return the offset of the first match or the 
 *   vector length if no match is found;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SVFIRST_SOURCE
#define SVFIRST_SOURCE

#include "../strlib/strlib.h"

size_t svfirst (char const * string, char const * vector [], size_t length, signed comp (char const *, char const *)) 

{
	size_t offset;

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

	for (offset = 0; offset < length; offset++) 
	{
		if (comp (string, vector [offset]) == 0) 
		{
			return (offset);
		}
	}
	return (length);
}


#endif

