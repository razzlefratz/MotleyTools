/*====================================================================*
 *
 *   bool listcreate(LIST * list, size_t size);
 *
 *   list.h
 *
 *   initialize a list structure by allocating an array of specified
 *   size and clearing array pointers and counters; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef LISTCREATE_SOURCE
#define LISTCREATE_SOURCE

#include <string.h>

#include "../list/list.h"
#include "../tools/memory.h"

bool listcreate (LIST * list, size_t size) 

{

#ifdef CMASSOC_SAFEMODE

	if (!list) 
	{
		return (false);
	}

#endif

	memset (list, 0, sizeof (* list));
	list->table = LST (char const *, (size + 1));
	if (list->table) 
	{
		list->block = size;
		list->limit = size;
		return (true);
	}
	return (false);
}


#endif

