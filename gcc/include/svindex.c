/*====================================================================*
 *
 *   size_t svindex (char const *name, char const *list[], size_t size, int (*comp)(char const *, char const *));
 *
 *   search an ordered string vector for string; return the vector
 *   index on match or the vector length on failure; by convention
 *   vector[length] is void; this function does not rely on that; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SVINDEX_SOURCE
#define SVINDEX_SOURCE

#include <string.h>

#include "../strlib/strlib.h"

size_t svindex (char const *title, char const *table [], size_t count, int (*comp)(char const *, char const *)) 

{
	size_t lower = 0;
	size_t upper = count;

#ifdef STRLIB_SAFEMODE

	if (title == (char const *) (0)) 
	{
		return (count);
	}
	if (table == (char const **) (0)) 
	{
		return (count);
	}
	if (comp == (void *) (0)) 
	{
		return (count);
	}

#endif

	while (lower < upper) 
	{
		size_t index = (lower + upper) >> 1;
		signed order = comp (title, table [index]);
		if (order < 0) 
		{
			upper = index - 0;
		}
		else if (order > 0) 
		{
			lower = index + 1;
		}
		else 
		{
			return (index);
		}
	}
	return (count);
}


#endif

