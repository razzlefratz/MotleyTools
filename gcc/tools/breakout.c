/*====================================================================*
 *
 *   void breakout (char const * string, size_t length);
 *
 *   format.h
 *
 *   print a multi-line script break using the string argument as 
 *   the bar title line;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef BREAKOUT_SOURCE
#define BREAKOUT_SOURCE

#include <stdio.h>

#include "../tools/format.h"

void breakout (char const * string, size_t length) 

{
	unsigned column;
	putc ('#', stdout);
	putc (' ', stdout);
	for (column = 2; column < length; column++) 
	{
		putc ('=', stdout);
	}
	putc ('\n', stdout);
	putc ('#', stdout);
	putc (' ', stdout);
	if (string) 
	{
		while (*string) 
		{
			putc (*string++, stdout);
		}
	}
	putc ('\n', stdout);
	putc ('#', stdout);
	putc (' ', stdout);
	for (column = 2; column < length; column++) 
	{
		putc ('-', stdout);
	}
	putc ('\n', stdout);
	putc ('\n', stdout);
	return;
}


#endif

