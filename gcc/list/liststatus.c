/*====================================================================*
 *
 *   void liststatus (LIST *list, FILE *file);
 *
 *   list.h
 *
 *   display the insternal state of a struct _list_ data type;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef LISTSTATUS_SOURCE
#define LISTSTATUS_SOURCE

#include <stdio.h>

#include "../list/list.h"

bool liststatus (LIST * list, FILE * file) 

{

#ifdef CMASSOC_SAFEMODE

	if (!list) 
	{
		return (false);
	}
	if (!file) 
	{
		return (false);
	}

#endif

	for (list->index = list->start; list->index < list->count; list->index++) 
	{
		fprintf (file, "list[" SIZE_T_SPEC "]=[%s]\n", list->index, list->table [list->index]);
	}
	fprintf (file, "\n");
	fprintf (file, "list->order = %d\n", list->order);
	fprintf (file, "list->error = %d\n", list->error);
	fprintf (file, "list->block = " SIZE_T_SPEC "\n", list->block);
	fprintf (file, "list->limit = " SIZE_T_SPEC "\n", list->limit);
	fprintf (file, "list->start = " SIZE_T_SPEC "\n", list->start);
	fprintf (file, "list->count = " SIZE_T_SPEC "\n", list->count);
	fprintf (file, "list->index = " SIZE_T_SPEC "\n", list->index);
	fprintf (file, "list->lower = " SIZE_T_SPEC "\n", list->lower);
	fprintf (file, "list->upper = " SIZE_T_SPEC "\n", list->upper);
	fprintf (file, "\n");
	fflush (file);
	return (true);
}


#endif

