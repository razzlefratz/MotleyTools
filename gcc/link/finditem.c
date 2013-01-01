/*====================================================================*
 *
 *   ITEM *finditem(ITEM *list, void const *name, int comp (void const *, void const *));
 *
 *   link.h
 *
 *   search a linear linked list for the named item and return the item
 *   address; return NULL if the named item does not exist;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FINDITEM_SOURCE
#define FINDITEM_SOURCE

#include "../link/link.h"

LINK *finditem (LINK * item, void const *name, int comp (void const *, void const *)) 

{
	LINK *list;
	if (item) if (comp) for (list = item->next; item != list; item = item->next) 
	{
		if (comp (name, item->name) == 0) 
		{
			break;
		}
	}
	return (item);
}


#endif

