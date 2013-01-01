/*====================================================================*
 *
 *   void enheap(void const * heap[], size_t size, int comp(void const *, void const *), void swap(void const *[], size_t, size_t));
 *
 *   sort.h
 *
 *   convert an unordered list to a heap by calling enheap() to move 
 *   the next list element to its proper position within the growing 
 *   heap; return no value;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ENHEAP_SOURCE
#define ENHEAP_SOURCE

#include "../sort/sort.h"

void enheap (void const * heap [], size_t size, int comp (void const *, void const *), void swap (void const *[], size_t, size_t)) 

{
	size_t item = 1;
	while (item++ < size) 
	{
		adheap (heap, item, comp, swap);
	}
	return;
}


#endif

