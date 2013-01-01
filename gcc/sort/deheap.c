/*====================================================================*
 *
 *   void deheap(void const * heap[], size_t size, int comp(void const *, void const *), void swap(void const *[], size_t, size_t));
 *
 *   sort.h
 *
 *   convert a heap to an ordered list by repeatedly swapping the 
 *   root with the last element then calling reheap() to position
 *   the root element in the diminished heap; return no value;
 *   
 *   the order of list elements will oppose that of the heap; for 
 *   example, a heap arranged in ascending order produces a list 
 *   arranged in descending order;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef DEHEAP_SOURCE
#define DEHEAP_SOURCE

#include "../sort/sort.h"

void deheap (void const * heap [], size_t size, int comp (void const *, void const *), void swap (void const *[], size_t, size_t)) 

{
	while (size > 1) 
	{
		swap (heap, 0, --size);
		reheap (heap, size, comp, swap);
	}
	return;
}


#endif

