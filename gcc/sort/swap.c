/*====================================================================*
 *
 *   void swap(void const *list[], size_t one, size_t two)
 *
 *   sort.h
 *
 *   exchange two pointers in a pointer list; 
 *
 *   this function can be passed to modular sort functions isort(), 
 *   psort(), ssort(), hsort(), adheap(), reheap(), enheap() and
 *   deheap(); 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SWAP_SOURCE
#define SWAP_SOURCE

#include "../sort/sort.h"

void swap (void const * list [], size_t one, size_t two) 

{
	if (one != two) 
	{
		void const * temp = list [one];
		list [one] = list [two];
		list [two] = temp;
	}
	return;
}


#endif

