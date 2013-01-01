/*====================================================================*
 *
 *   void psort(void const *list[], size_t size, int comp(void const *, void const *), void swap(void const *[], size_t, size_t));
 *
 *   sort.h
 *
 *   arrange elements of an unordered list using a 'quick' or 'partition'
 *   or 'pivot' sort algorithm;
 *
 *   this particular implementation uses a 'fat pivot' to minimize the
 *   number of exchanges when the list contains repetitive elements.
 *
 *   For more information on the quicksort algorithm see:
 *
 *   1. "Fundamentals of Computer Algorithms" by Horowitz and Sahni;
 *   2. "Fundamental Algorithms: Search & Sorting" by Donald Knuth;
 *   3. "Software Tools" by Kernighan and Plaugher;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef PSORT_SOURCE
#define PSORT_SOURCE

#include "../sort/sort.h"

void psort (void const *list [], size_t size, int comp (void const *, void const *), void swap (void const *[], size_t, size_t)) 

{
	size_t lower = 0;
	size_t index = size >> 1;
	size_t upper = size;
	if (index > 0) 
	{
		swap (list, 0, index);
		index = lower;
		while (++index < upper) 
		{
			if (comp (list [index], list [0]) < 0) 
			{
				swap (list, ++lower, index);
			}
		}
		index = upper;
		while (--index > lower) 
		{
			if (comp (list [index], list [0]) > 0) 
			{
				swap (list, --upper, index);
			}
		}
		swap (list, 0, index);
		psort (list + upper, size - upper, comp, swap);
		psort (list, lower, comp, swap);
	}
	return;
}


#endif

