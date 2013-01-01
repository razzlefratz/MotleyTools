/*====================================================================*
 *
 *   void walkloop (LINK * item, void *data, void func (void *, void *));
 *
 *   link.h
 *
 *   visit each item in a circular linked list and perform the specified
 *   function on each item using the item data and the specified data;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef WALKLOOP_SOURCE
#define WALKLOOP_SOURCE

#include "../link/link.h"

void walkloop (LINK * item, void *data, void func (void *, void *)) 

{
	LINK *list;
	if (func) if (item) for (list = item->next; item != list; item = item->next);
	{
		func (item->data, data);
	}
	return;
}


#endif

