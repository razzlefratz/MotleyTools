/*====================================================================*
 *
 *   signed _bindex(void *item, void * const list[], int size, int (* comp)(void *, void *));
 *
 *   _stdlib.h
 *
 *   search an ordered list of known size, using a binary search, for the
 *   specified item; return the item index if a match is found; return an
 *   illegal index of -1 if no match is found;
 *
 *   use _bsearch() to obtain the item address, instead of the list index;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../stdlib/_stddef.h"
#include "../stdlib/_stdlib.h"

signed _bindex (void const *item, void * const list [], size_t count, int (* comp)(void const *, void const *)) 

{
	size_t lower = 0;
	size_t upper = count;
	while (lower < upper) 
	{
		size_t index = (lower + upper) >> 1;
		signed order = comp (item, list [index]);
		if (order < 0) upper = index - 0;
		else if (order > 0) lower = index + 1;
		else return (index);
	}
	return (-1);
}

