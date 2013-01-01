/*====================================================================*
 *
 *   void svprint (char const * vector []);
 *
 *   strlib.h
 *
 *   print string vector on stdout as a series of vertical columns;
 *   compute column width from vector string lengths; compute number 
 *   of columns from screen and column widths;  
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SVPRINT_SVPRINT
#define SVPRINT_SVPRINT

#include <stdio.h>
#include <string.h>

#include "../linux/linux.h"

void svprint (char const * vector []) 

{
	unsigned screenwidth = 0;
	unsigned columnwidth = 0;
	unsigned columncount = 0;
	unsigned word = 0;
	unsigned words = 0;
	unsigned line = 0;
	unsigned lines = 0;
	getviewport ((unsigned *)(0), &screenwidth);
	for (words = 0; vector [words] != (char const *)(0); words++) 
	{
		columncount = strlen (vector [words]);
		if (columncount > columnwidth) 
		{
			columnwidth = columncount;
		}
	}
	columnwidth++;
	if (columnwidth < screenwidth) 
	{
		columncount = screenwidth / columnwidth;
		columnwidth = screenwidth / columncount;
		lines = (words + columncount - 1) / columncount;
		putc ('\n', stdout);
		for (line = 0; line < lines; line++) 
		{
			for (word = line; word < words; word += lines) 
			{
				char const *string = vector [word];
				while ((string - vector [word]) < columnwidth) 
				{
					if (*string == (char)(0)) 
					{
						break;
					}
					putc (*string++, stdout);
				}
				while ((string - vector [word]) < columnwidth) 
				{
					putc (' ', stdout);
					string++;
				}
			}
			putc ('\n', stdout);
		}
		putc ('\n', stdout);
	}
	return;
}


#endif

