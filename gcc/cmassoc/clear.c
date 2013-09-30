/*====================================================================*
 *
 *   clear.c - clear terminal screen an reposition cursor;
 *
 *   this program converts all ASCII control characters   to a visible,
 *   or printable, display format; the display mode is selectable, as
 *   either an ASCII, ANSI, or UNIX escape sequence;
 *
 *   $ clear [-tbh]
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#endif

/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv [])

{
	static char const * optv [] =
	{
		"tmb",
		PUTOPTV_S_FUNNEL,
		"clear screen and position cursor",
		"t\ttop of screen",
		"m\tmiddle of screen",
		"b\tbottom of screen",
		(char const *) (0)
	};
	unsigned line;
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 't':
			line = 0;
			break;
		case 'm':
			line = VT_LINES >> 1;
			break;
		case 'b':
			line = VT_LINES;
			break;
		default: 
			break;
		}
	}
	fprintf (stderr, "\033[2J\033[%2d;1H", line);
	exit (0);
}

