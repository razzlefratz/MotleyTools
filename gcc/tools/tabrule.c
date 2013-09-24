/*====================================================================*
 *
 *   void tabrule(size_t length);
 *
 *   Display a text ruler showing current tabstop settings on stdout.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef TABRULE_SOURCE
#define TABRULE_SOURCE

#include <stdio.h>
#include "../tools/tabs.h"

void tabrule(size_t length)

{
	size_t column = 0;
	while (column < length)
	{
		putchar (column? '^': '0' + column % 10);
		column++;
	}
	putchar ('\n');
	return;
}

#endif



