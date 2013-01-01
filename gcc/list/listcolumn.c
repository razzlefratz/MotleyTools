/*====================================================================*
 *
 *   void listcolumn(LIST *list, FILE *file, unsigned width, unsigned count, bool index);
 *
 *   print list as a series of (count) vertical columns with optional 
 *   index numbers; compute column width from list string lengths and inter-column
 *   spacing; compute number of columns from screen and column widths;  
 *
 *   if width is 0 then use the terminal window column width; if
 *   count is 0 then compute based on width and field; otherwise,
 *   compute field based on width and count;
 * 
 *   if index is true then prefix strings with index numbers; 
 * 
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef LISTCOLUMN_SOURCE
#define LISTCOLUMN_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../list/list.h"
#include "../linux/linux.h"
#include "../tools/format.h"

void listcolumn (LIST * list, FILE * file, unsigned width, unsigned count, bool index) 

{
	unsigned digit = 0;
	unsigned field = 0;
	unsigned block = 0;

#ifdef CMASSOC_SAFEMODE

	if (!list) 
	{
		return;
	}
	if (!file) 
	{
		return;
	}

#endif

	if (index) 
	{
		for (list->index = list->count; list->index > 0; list->index /= 10) 
		{
			digit++;
		}
		digit++;
	}
	if (!width) 
	{
		width = 78;
		getviewport ((unsigned *)(0), &width);
	}
	if (!count) 
	{
		for (list->index = list->start; list->index < list->count; list->index++) 
		{
			block = strlen (list->table [list->index]);
			if (block > field) 
			{
				field = block;
			}
		}
		field++;
	}
	if (!field) 
	{
		field = (width / count) - digit;
	}
	count = width / (digit + field);
	field = (width / count) - digit;
	block = (list->count + count - 1) / count;
	for (list->lower = list->start; list->lower < block; list->lower++) 
	{
		for (list->upper = list->lower; list->upper < list->count; list->upper += block) 
		{
			if (digit != 0) 
			{

#ifdef __APPLE__

				printf (" %-*.*lu", (int)(digit-1), (int)(digit-1), list->upper);

#else

				printf (" %-*.*u", (int)(digit-1), (int)(digit-1), list->upper);

#endif

			}
			printf (" %-*.*s", (int)(field-1), (int)(field-1), list->table [list->upper]);
		}
		putc ('\n', stdout);
	}
	return;
}


#endif

