/*====================================================================*
 *
 *   void sift (void const *list[], size_t size, size_t step, int comp(void const *, void const *), void swap(void const *[], size_t, size_t));
 *
 *   sort.h
 *
 *   merge the last item of an ordered list into the list;
 *
 *   this function is the primative of an insertion sort, the simplest of
 *   sorting algorithms; it may be passed to function isort() and ssort();
 *
 *   for more information on this sort algorithm see:
 *
 *   1. 'Sorting and Searching' by Donald Knuth; Vol III; algorithm S;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SIFT_SOURCE
#define SIFT_SOURCE

#include "../sort/sort.h"

void sift (void const *list [], size_t size, size_t step, int comp (void const *, void const *), void swap (void const *[], size_t, size_t)) 

{
	void const *item;

#ifdef CMASSOC_SAFEMODE

	if (list == (void const *) (0)) 
	{
		return;
	}

#endif

	for (item = list [size]; size >= step; size -= step) 
	{
		if (comp (item, list [size - step]) >= 0) 
		{
			break;
		}
		swap (list, size, size - step);
	}
	list [size] = item;
	return;
}


#endif

