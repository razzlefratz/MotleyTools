/*====================================================================*
 *
 *   size_t vfirst(void const *item, void const *list[], size_t size, int comp (void const *, void const *))
 *
 *   sort.h
 *
 *   search a list of known size, front to back, for item;
 *   return the index of the first match found; return the list size 
 *   if no match is found;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef VFIRST_SOURCE
#define VFIRST_SOURCE

#include "../sort/sort.h"

size_t vfirst (void const *item, void const *list [], size_t size, int comp (void const *, void const *)) 

{
	size_t next;

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

	for (next = 0; next < size; next++) 
	{
		if (comp (item, list [next]) == 0) 
		{
			return (next);
		}
	}
	return (size);
}


#endif

