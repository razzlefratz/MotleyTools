/*====================================================================*
 *
 *   size_t svindex(char const *string, char const *vector[], size_t length, int (* comp)(void const *, void const *))
 *
 *   strlib.h
 *
 *   search an ordered vector of known length (using binary search) 
 *   for the specified string; return the string index if a match is 
 *   found; return (size_t)(-1) if no match is found;
 *
 *   see _bsearch() in _stdlib.h for similar functionality;
 *
 *.  published 2003 by voidles maier associates limited for internal use;
 *:  modified sun 07 sep 03 by user root on host zeus;
 *;  compiled for debian gnu/linux using gcc compiler;
 *
 *--------------------------------------------------------------------*/

#ifndef SVINDEX_SOURCE
#define SVINDEX_SOURCE

#include "../tools/strlib.h"
 
size_t svindex (char const *string, char const *vector [], size_t length, int (*comp) (char const *, char const *)) 

{
	size_t lower = 0;
	size_t upper = length;

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
	return (length);
}

#endif
 

