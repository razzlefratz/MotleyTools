/*====================================================================*
 *
 *   LINK *queue(LINK *list, LINK *item)
 *
 *   link.h
 *
 *   This function can either append two circular link lists or break
 *   one list into two, depending on the argument order.
 *
 *   A circular list has no clear start or end. Once the address of an
 *   item is known any other item can be found by following links. The
 *   last item is often used as a marker since the first item is just
 *   one link away.
 *
 *   Circular lists are merged by exchanging the link of an item in one
 *   list with the link of any item in the other. Either item may then
 *   serve as the last item of the merged list.
 *
 *   This appends the second list to the first and returns the address
 *   if the last item of the new list, which is also the last item of
 *   the old second list.
 *
 *      marker = queue(list,item)
 *
 *   As it turns out, breaking one list into two can be done by marking
 *   any two items in the list and exchanging their links. We then have
 *   two markers, each pointing to the end of a different list.
 *
 *   This can append one list to another, returning apointer to the tail
 *   of the second.
 *
 *      head = queue(list,item); returns head portion of list
 *      tail = queue(item,list); returns tail portion of list
 *
 *   These definitions might be used to perform some basic list or stack
 *   type operations.
 *
 *   #define _post(list,item) list = queue(list,item)
 *   #define _push(list,item) list = queue(item,list)
 *   #define  _pop(list,item) item = queue(list,list->next)
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef QUEUE_SOURCE
#define QUEUE_SOURCE

#include "../link/link.h"

LINK *queue (LINK * list, LINK * item) 

{
	LINK *temp;
	if (item == (LINK *) (0)) 
	{
		return (list);
	}
	if (list == (LINK *) (0)) 
	{
		return (item);
	}
	if (item != list) 
	{
		temp = item->next;
		item->next = list->next;
		list->next = temp;
	}
	return (item);
}


#endif

