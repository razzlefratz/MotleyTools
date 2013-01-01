/*====================================================================*
 *
 *   LINK *stackpop(LINK *list);
 *
 *   link.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STACKPOP_SOURCE
#define STACKPOP_SOURCE

#include <stdlib.h>

#include "../link/link.h"

LINK *stackpop (LINK * list) 

{
	if (list != (LINK *) (0)) 
	{
		LINK *item = list;
		list = list->next;
		free (item->name);
		free (item);
	}
	return (list);
}


#endif

