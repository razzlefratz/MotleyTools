/*====================================================================*
 *
 *   size_t vfinal(void const *item, void const *list[], size_t size, int comp (void const *, void const *))
 *
 *   sort.h
 *
 *   search a list of known size, back to front, for the specified item;
 *   return the index of the last match or -1 if no match is found;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef VFINAL_SOURCE
#define VFINAL_SOURCE

#include "../sort/sort.h"

size_t vfinal (void const *item, void const *list [], size_t size, int comp (void const *, void const *)) 

{
	size_t next = size;

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

	while (next-- > 0) 
	{
		if (comp (item, list [next]) == 0) 
		{
			return (next);
		}
	}
	return (size);
}


#endif

