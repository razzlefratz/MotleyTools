/*====================================================================*
 *
 *   void *_bsearch(void *item, void * const list[], size_t listsize, int (* comp)(void const *, void const *));
 *
 *   _stdlib.h
 *
 *   search an ordered list of known size, using a binary search, for the
 *   specified item; return the item address if a match is found; return
 *   NULL if no match is found;
 *
 *   use _bindex() to obtain the list index, instead of the item address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../stdlib/_stddef.h"
#include "../stdlib/_stdlib.h"

void *_bsearch (void const *item, void * const list [], size_t listsize, int (* comp)(void const *, void const *)) 

{
	size_t lower = 0;
	size_t upper = listsize;
	while (lower < upper) 
	{
		size_t index = (lower + upper) >> 1;
		signed order = comp (item, list [index]);
		if (order < 0) upper = index - 0;
		else if (order > 0) lower = index + 1;
		else return (list [index]);
	}
	return ((void *)(0));
}

