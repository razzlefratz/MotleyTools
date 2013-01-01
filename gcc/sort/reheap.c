/*====================================================================*
 *
 *   void reheap(void const * heap[], size_t size, int comp(void const *, void const *), void swap(void const *[], size_t, size_t));
 *
 *   sort.h
 *
 *   adjust a binary heap by moving the root element to the proper 
 *   position within the heap; return no value.
 *
 *   this implementation simplifies the algorithm by decrementing the
 *   heap base address so that the index of the first heap element is
 *   1 instead of 0 and that of the last heap element is size instead 
 *   of size-1.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef REHEAP_SOURCE
#define REHEAP_SOURCE

#include <stdio.h>
#include "../sort/sort.h"

void reheap (void const * heap [], size_t size, int comp (void const *, void const *), void swap (void const *[], size_t, size_t)) 

{
	size_t root;
	size_t leaf;
	--heap;
	for (root = leaf = 1; (leaf <<= 1) <= size; root = leaf) 
	{
		if (leaf < size) 
		{
			if (comp (heap [leaf], heap [leaf + 1]) > 0) 
			{
				++leaf;
			}
		}
		if (comp (heap [root], heap [leaf]) > 0) 
		{
			swap (heap, root, leaf);
			continue;
		}
		break;
	}
	return;
}


#endif

