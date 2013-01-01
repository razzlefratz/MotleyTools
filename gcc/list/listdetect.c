/*====================================================================*
 *
 *   bool listdetect(LIST * list, char const * item);
 *
 *   list.h
 *
 *   search an ordered list for the string argument; return true if the
 *   list contains another string having the same content; return false
 *   if not; this function can be used to detect string duplicates before
 *   inserton; function listinsert() calls this function by default;
 *
 *   string detection uses a binary search pattern; this means the result 
 *   is reliable if strings are in ascending order; duplicate strings may
 *   be present if they are adjacent;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef LISTDETECT_SOURCE
#define LISTDETECT_SOURCE

#include <string.h>

#include "../list/list.h"

bool listdetect (LIST * list, char const * item) 

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

	list->lower = list->start;
	list->upper = list->count;
	while (list->lower < list->upper) 
	{
		list->index = (list->lower + list->upper) >> 1;
		list->order = strcmp (item, list->table [list->index]);
		if (list->order < 0) 
		{
			list->upper = list->index - 0;
			continue;
		}
		if (list->order > 0) 
		{
			list->lower = list->index + 1;
			continue;
		}
		return (true);
	}
	return (false);
}


#endif

