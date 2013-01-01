/*====================================================================*
 *
 *   void listdelete(LIST * list);
 *
 *   list.h
 *
 *   delete the contents of a list by releasing memory used to store
 *   strings and reseting internal pointers and counters; list block
 *   and limit are cleared;
 * 
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef LISTDELETE_SOURCE
#define LISTDELETE_SOURCE

#include <stdlib.h>
#include <memory.h>

#include "../list/list.h"

bool listdelete (LIST * list) 

{

#ifdef CMASSOC_SAFEMODE

	if (!list) 
	{
		return (false);
	}

#endif

	if (!list->table) 
	{
		return (false);
	}
	while (list->count--) 
	{
		free ((char *) (list->table [list->count]));
		list->table [list->count] = (char const *) (0);
	}
	free (list->table);
	memset (list, 0, sizeof (* list));
	return (true);
}


#endif

