/*====================================================================*
 *
 *   int svfirst(char const *string, char const *vector[], size_t length, int (* comp)(char const *, char const *))
 *
 *   search a list of known size, front to back, for the specified item;
 *   return the index of the first match or the list size if no match is
 *   found;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SVFIRST_SOURCE
#define SVFIRST_SOURCE

#include "../strlib/strlib.h"

size_t svfirst (char const *title, char const *table [], size_t count, int (* comp)(char const *, char const *)) 

{
	size_t index;

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

	for (index = 0; index < count; index++) 
	{
		if (comp (title, table [index]) == 0) 
		{
			return (index);
		}
	}
	return (count);
}


#endif

