/*====================================================================*
 *
 *   bool listsort (LIST * list);
 *
 *   list.h
 *
 *   sort an existing list;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef LISTSORT_SOURCE
#define LISTSORT_SOURCE

#include <string.h>

#include "../list/list.h"

bool listsort (LIST * list) 

{

#ifdef CMASSOC_SAFEMODE

	if (!list) 
	{
		return (false);
	}

#endif

	size_t limit = list->count;
	for (list->count = list->start; list->count < limit; list->count++) 
	{
		char const * item = list->table [list->count];
		listdetect (list, item);
		for (list->upper = list->count; list->upper > list->lower; list->upper--) 
		{
			list->table [list->upper] = list->table [list->upper - 1];
		}
		list->table [list->upper] = item;
	}
	return (true);
}


#endif

