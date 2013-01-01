/*====================================================================*
 *
 *   size_t vindex(void const *item, void const *list[], size_t size, int comp (void const *, void const *))
 *
 *   sort.h
 *
 *   search an ordered list of known size for the specified item; 
 *   return the item index if found or an illegal index if -1 if 
 *   not found; use simple binary search; 
 *
 *   see _bsearch() in _stdlib.h for similar functionality;.
 *   see strindex() in strlib.h for similar functionality;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef VINDEX_SOURCE
#define VINDEX_SOURCE

#include "../sort/sort.h"

size_t vindex (void const *item, void const *list [], size_t size, int comp (void const *, void const *)) 

{
	size_t lower = 0;
	size_t upper = size;

#ifdef CMASSOC_SAFEMODE

	if (item == (void *) (0)) 
	{
		return (size);
	}
	if (list == (void *) (0)) 
	{
		return (size);
	}
	if (comp == (void *) (0)) 
	{
		return (size);
	}

#endif

	while (lower < upper) 
	{
		size_t index = (lower + upper) >> 1;
		signed order = comp (item, list [index]);
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
	return (size);
}


#endif

