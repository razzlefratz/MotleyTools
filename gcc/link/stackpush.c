/*====================================================================*
 *
 *   LINK *stackpush(LINK *list, void const *name, void const *data);
 *
 *   link.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STACKPUSH_SOURCE
#define STACKPUSH_SOURCE

#include "../link/link.h"
#include "../tools/memory.h"

LINK *stackpush (LINK * list, void const *name, void const *data) 

{
	LINK *item = NEW (LINK);
	item->name = (void *) (name);
	item->data = (void *) (data);
	item->next = list;
	return (item);
}


#endif

