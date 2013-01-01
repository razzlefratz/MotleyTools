/*====================================================================*
 *
 *   size_t svindex(char const *string, char const * vector[], size_t length, signed comp (void const *, void const *))
 *
 *   strlib.h
 *
 *   search an ordered vector of known length (using binary search) 
 *   for the specified string; return the string index if a match is 
 *   found; return (size_t)(-1) if no match is found;
 *
 *   see _bsearch() in _stdlib.h for similar functionality;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SVINDEX_SOURCE
#define SVINDEX_SOURCE

#include "../strlib/strlib.h"

size_t svindex (char const *string, char const * vector [], size_t length, signed comp (char const *, char const *)) 

{
	size_t lower = 0;
	size_t upper = length;

#ifdef CMASSOC_SAFEMODE

	if (!string) 
	{
		return (length);
	}
	if (!vector) 
	{
		return (length);
	}
	if (!comp) 
	{
		return (length);
	}

#endif

	while (lower < upper) 
	{
		size_t index = (lower + upper) >> 1;
		signed order = comp (string, vector [index]);
		if (order < 0) 
		{
			upper = index - 0;
			continue;
		}
		if (order > 0) 
		{
			lower = index + 1;
			continue;
		}
		return (index);
	}

#if 1

	return ((size_t)(-1));

#else

	return (length);

#endif

}


#endif

