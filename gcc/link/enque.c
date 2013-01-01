/*====================================================================*
 *
 *   LINK *enque(LINK *list, LINK *item)
 *
 *   link.h
 *
 *   append an item to a NULL terminated linked list; returns the address
 *   of the first list item; the item may, itself, be the first item;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ENQUE_SOURCE
#define ENQUE_SOURCE

#include "../link/link.h"

LINK *enque (LINK * list, LINK * item) 

{
	LINK *temp = list;
	if (!list) 
	{
		return (item);
	}
	while (temp->next) 
	{
		temp = temp->next;
	}
	temp->next = item;
	return (list);
}


#endif

