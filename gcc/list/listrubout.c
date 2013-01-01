/*====================================================================*
 *
 *   void listrubout(LIST * list);
 *
 *   list.h
 *
 *   rubout the contents of a list by releasing memory used to store
 *   strings; reset internal pointers and counters; leave list block
 *   and limit unchanged; this means that big lists stay big;
 * 
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef LISTRUBOUT_SOURCE
#define LISTRUBOUT_SOURCE

#include <stdlib.h>

#include "../list/list.h"

bool listrubout (LIST * list) 

{

#ifdef CMASSOC_SAFEMODE

	if (!list) 
	{
		return (false);
	}

#endif

	while (list->count--) 
	{
		free ((char *) (list->table [list->count]));
		list->table [list->count] = (char const *) (0);
	}
	list->order = 0;
	list->error = 0;
	list->start = 0;
	list->count = 0;
	list->index = list->start;
	list->lower = list->start;
	list->upper = list->count;
	list->point = list->start;
	return (true);
}


#endif

