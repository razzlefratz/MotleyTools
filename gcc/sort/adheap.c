/*====================================================================*
 *
 *   void adheap (void const * heap[], size_t size, int comp(void const *, void const *), void swap(void const *[], size_t, size_t));
 *
 *   sort.h
 *
 *   adjust a binary heap by moving the last element to the proper position
 *   within the heap; return no value;
 *
 *   this implementation simplifies the algorithm by decrementing 
 *   the heap address so that that the index of the root element 
 *   is 1 instead of 0 and the index of the last heap element is
 *   size instead of size-1.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ADHEAP_SOURCE
#define ADHEAP_SOURCE

#include "../sort/sort.h"

void adheap (void const * heap [], size_t size, int comp (void const *, void const *), void swap (void const *[], size_t, size_t)) 

{
	size_t root;
	size_t leaf;
	--heap;
	for (root = leaf = size; root >>= 1; leaf = root) 
	{
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

