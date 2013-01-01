/*====================================================================*
 *
 *   void qsort (void *list[], size_t listsize, int comp(void const *, void const *));
 *
 *   sort.h
 *
 *   sorts element of a list using a 'partition' or 'quick' sort; the list
 *   order depends on the comparison function used; return no value;
 *
 *   This particular implementation uses a 'fat pivot' to minimize the
 *   the number of element exchanges when the list contains repetitive
 *   elements. An external function is used to exchange elements. This
 *   makes the logic easier to understand and maintain.
 *
 *   the itemsize argument is ignored in this implementation; it exists as
 *   an argument to satisfy posix and other standards; we might discover a
 *   use for it some day and want it back;
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

#include "../sort/sort.h"

void qsort (void const *list [], size_t size, int comp (void const *, void const *)) 

{
	size_t lower = 0;
	size_t pivot = size >> 1;
	size_t upper = size;
	if (pivot > 0) 
	{
		swap (list, 0, pivot);
		pivot = lower;
		while (++pivot < upper) 
		{
			if (comp (list [pivot], list [0]) < 0) 
			{
				swap (list, pivot, ++lower);
			}
		}
		pivot = upper;
		while (--pivot > lower) 
		{
			if (comp (list [pivot], list [0]) > 0) 
			{
				swap (list, pivot, --upper);
			}
		}
		swap (list, 0, pivot);
		qsort (list + upper, size - upper, comp);
		qsort (list, lower, comp);
	}
	return;
}

