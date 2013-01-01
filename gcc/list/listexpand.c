/*====================================================================*
 *
 *   bool listexpand(LIST * list);
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

#ifndef LISTEXPAND_SOURCE
#define LISTEXPAND_SOURCE

#include <string.h>

#include "../list/list.h"
#include "../tools/memory.h"

bool listexpand (LIST * list) 

{

#ifdef CMASSOC_SAFEMODE

	if (!list) 
	{
		return (false);
	}

#endif

	if (++list->count < list->limit) 
	{
		return (false);
	}
	list->limit = list->limit + list->block;
	list->block = list->limit - list->block;
	list->table = (char const **) (erealloc (list->table, sizeof (char const *) * (list->limit + 1)));
	return (true);
}


#endif

