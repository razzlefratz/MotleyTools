/*====================================================================*
 *
 *   bool listremove (LIST * list, char const * item);
 *
 *   list.h
 *
 *   insert a copy of the string argument into a sorted list provided
 *   another string having identical content is not present; the result
 *   is an order list of unique string values; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef LISTREMOVE_SOURCE
#define LISTREMOVE_SOURCE

#include <string.h>
#include <stdlib.h>

#include "../list/list.h"

bool listremove (LIST * list, char const * item) 

{

#ifdef CMASSOC_SAFEMODE

	if (!list) 
	{
		return (false);
	}
	if (!item) 
	{
		return (false);
	}

#endif

	if (listdetect (list, item)) 
	{
		free ((char *)(list->table [list->lower]));
		for (list->index = list->lower; list->index < list->count; list->index++) 
		{
			list->table [list->index] = list->table [list->index+1];
		}
		list->table [list->count--] = (char const *) (0);
		return (true);
	}
	return (false);
}


#endif

