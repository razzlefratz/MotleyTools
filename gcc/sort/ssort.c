/*====================================================================*
 *
 *  void ssort (void const *list[], size_t size, int comp (void const *, void const *), void swap (void const *[], size_t, size_t), void sift (void const *[], size_t, size_t, int comp (void const *, void const *), void swap (void const *[], size_t, size_t)));
 *
 *   ssort.h
 *
 *   arrange elements of an unordered list using a 'diminishing increment'
 *   or 'shell' sort algorithm;
 *
 *   See alorithm D in "Sorting and Searching" by Donald Knuth or the
 *   shell() function in "Software Tools" by Kernighan and Plaugher.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SSORT_SOURCE
#define SSORT_SOURCE

#include "../sort/sort.h"

void ssort (void const *list [], size_t size, int comp (void const *, void const *), void swap (void const *[], size_t, size_t), void sift (void const *[], size_t, size_t, int comp (void const *, void const *), void swap (void const *[], size_t, size_t))) 

{
	size_t step;
	size_t last;
	for (step = size >> 1; step > 0; step >>= 1) 
	{
		for (last = step; last < size; last++) 
		{
			sift (list, last, step, comp, swap);
		}
	}
	return;
}


#endif

