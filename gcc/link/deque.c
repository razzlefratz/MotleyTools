/*====================================================================*
 *
 *   LINK *deque(LINK *list);
 *
 *   link.h
 *
 *   unlink the first item from a linear linked list; return the address
 *   of the next list item; set the pointer of the unlinked item to NULL;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef DEQUE_SOURCE
#define DEQUE_SOURCE

#include "../link/link.h"

LINK *deque (LINK * list) 

{
	if (list) 
	{
		LINK *temp = list;
		list = temp->next;
		temp->next = (LINK *) (0);
	}
	return (list);
}


#endif

