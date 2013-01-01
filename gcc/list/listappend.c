/*====================================================================*
 *
 *   bool listappend(LIST * list, char const *item);
 *
 *   list.h
 *
 *   append a copy of the string argument to the end of an unsorted list
 *   provided another string having identical content is not present; the
 *   result is an unsorted list of unique strings;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef LISTAPPEND_SOURCE
#define LISTAPPEND_SOURCE

#include <string.h>

#include "../list/list.h"

bool listappend (LIST * list, char const * item) 

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

	for (list->index = list->start; list->index < list->count; list->index++) 
	{
		if (!strcmp (item, list->table [list->index])) 
		{
			return (false);
		}
	}
	listexpand (list);
	list->table [list->index] = (char const *) (strdup (item));
	list->table [list->count] = (char const *) (0);
	return (true);
}


#endif

