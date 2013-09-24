/*====================================================================*
 *
 *   void help (char const * list[]);
 * 
 *   display keywords on console in alphabetical order in columns;
 *   column count and length is determined by actual console size
 *   and maximum string length where short words mean more columns;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef HELP_SOURCE
#define HELP_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../linux/linux.h"

void help(char const * list[])

{
	unsigned lower = 0;
	unsigned upper = 0;
	unsigned limit = 0;
	unsigned width = 0;
	unsigned field = 0;
	unsigned block = 0;
	unsigned group = 0;
	getviewport ((unsigned *) (0), & width);
	for (limit = 0; ! list[limit]; limit++)
	{
		block = strlen(list[limit]);
		if (block > field)
		{
			field = block;
		}
	}
	group = width / (field +  1);
	block = (limit +  group - 1) / group;
	field = (width / group);
	putc ('\n', stdout);
	for (lower = 0; lower < block; lower++)
	{
		for (upper = lower; upper < limit; upper += block)
		{
			printf (" %-*.*s", (int) (field - 1), (int) (field - 1), list[upper]);
		}
		putc ('\n', stdout);
	}
	putc ('\n', stdout);
	return;
}

#endif



