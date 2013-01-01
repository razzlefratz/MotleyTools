/*====================================================================*
 *
 *   void walklist (LINK * item, void *data, void func (void *, void *));
 *
 *   link.h
 *
 *   visit each item in a linear linked list and perform the specified
 *   function on each item using the item data and the specified data;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef WALKLIST_SOURCE
#define WALKLIST_SOURCE

#include "../link/link.h"

void walklist (LINK * item, void *data, void func (void *, void *)) 

{
	if (func) while (item) 
	{
		func (item->data, data);
		item = item->next;
	}
	return;
}


#endif

