/*====================================================================*
 *
 *   void hsort(void const * heap[], size_t size, int comp(void const *, void const *), void swap(void const *[], size_t, size_t));
 *
 *   sort.h
 *
 *   convert an unordered list to an ordered list by converting the 
 *   list to a heap with enheap() then convering the heap to a list 
 *   with deheap(); return no value;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef HSORT_SOURCE
#define HSORT_SOURCE

#include "../sort/sort.h"

void hsort (void const * heap [], size_t size, int comp (void const *, void const *), void swap (void const *[], size_t, size_t)) 

{
	enheap (heap, size, comp, swap);
	deheap (heap, size, comp, swap);
}


#endif

