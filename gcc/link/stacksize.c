/*====================================================================*
 *
 *   unsigned stacksize(LINK *list);
 *
 *   link.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STACKSIZE_SOURCE
#define STACKSIZE_SOURCE

#include "../link/link.h"

size_t stacksize (LINK * list) 

{
	size_t size;
	for (size = 0; list != (LINK *) (0); size++) 
	{
		list = list->next;
	}
	return (size);
}


#endif

