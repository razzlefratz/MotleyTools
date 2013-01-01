/*====================================================================*
 *
 *   void stackclear(LINK *list);
 *
 *   link.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STACKCLEAR_SOURCE
#define STACKCLEAR_SOURCE

#include <stdlib.h>

#include "../link/link.h"

LINK *stackclear (LINK * list) 

{
	while (list != (LINK *)(0)) 
	{
		LINK *item = list;
		list = list->next;
		free (item->name);
		free (item);
	}
	return (list);
}


#endif

