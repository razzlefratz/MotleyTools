/*====================================================================*
 *
 *   void menushow (MENU *menu, signed screen);
 *
 *   menu.h 
 *
 *   print a multi-column list of menu items on stdout;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "../menu/menu.h"
#include "../tools/memory.h"

void menushow (MENU * menu, char buffer [], signed length) 

{
	unsigned rows = 0;
	unsigned cols = 0;
	unsigned row;
	unsigned col;
	unsigned item;
	unsigned items = menusize (menu);
	char ** list = emalloc (items * sizeof (char *));
	menulist (menu, buffer, buffer, length, list, items);
	for (item = 0; item < items; item++) 
	{
		if (strlen (list [item]) > cols) 
		{
			cols = strlen (list [item]);
		}
	}
	cols++;
	length--;
	rows = length / cols;

// printf ("length=%d size=%d rows=%d cols=%d\n", length,items,rows,cols);

	rows = (items + rows + 1) / rows;

// printf ("length=%d size=%d rows=%d cols=%d\n", length,items,rows,cols);

	for (row = 0; row < rows; row++) 
	{
		for (item = row; item < items; item += rows) 
		{
			char *sp = list [item];
			putc (' ', stdout);
			for (col = 0; col < cols; col++) 
			{
				putc (*sp? *sp++: '.', stdout);
			}
		}
		putc ('\n', stdout);
	}
	for (item = 0; item < items; item++) 
	{
		free (list [item]);
	}
	free (list);
	return;
}

