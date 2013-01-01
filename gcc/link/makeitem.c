/*====================================================================*
 *
 *   LINK *makeitem(void const *name, void const *data);
 *
 *   link.h
 *
 *   allocate an LINK structure and initialize it with the specified 
 *   name and data values; link the item to itself; return the item 
 *   address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MAKEITEM_SOURCE
#define MAKEITEM_SOURCE

#include "../link/link.h"
#include "../tools/memory.h"

LINK *makeitem (void const *name, void const *data) 

{
	LINK *item = NEW (LINK);
	item->name = (void *)(name);
	item->data = (void *)(data);
	item->next = item;
	return (item);
}


#endif

