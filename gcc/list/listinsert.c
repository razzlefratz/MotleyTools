/*====================================================================*
 *
 *   bool listinsert(LIST * list, char const * item);
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

#ifndef LISTINSERT_SOURCE
#define LISTINSERT_SOURCE

#include <string.h>

#include "../list/list.h"

bool listinsert (LIST * list, char const * item) 

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
		return (false);
	}
	listexpand (list);
	for (list->upper = list->count; list->upper > list->lower; list->upper--) 
	{
		list->table [list->upper] = list->table [list->upper-1];
	}
	list->table [list->upper] = (char const *) (strdup (item));
	list->table [list->count] = (char const *) (0);
	return (true);
}


#endif

