/*====================================================================*
 *
 *   header.c - output file headers;
 *
 *   copy first n lines of one or more text files to stdout;
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
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../tools/vtdef.h"
#include "../linux/linux.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#include "../tools/efreopen.c"
#include "../tools/emalloc.c"
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#endif

#ifndef MAKEFILE
#include "../linux/getviewport.c"
#endif

/*====================================================================*
 *
 *   void function (signed count, signed width);
 *
 *   read stdin and write stdout; print the first count input lines 
 *   and truncate output lines to width columns;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (signed count, signed width) 

{
	signed column = 0;
	signed c = getc (stdin);
	while ((count) && (c != EOF)) 
	{
		if (c == '\n') 
		{
			column = width;
			count--;
		}
		if (column < width) 
		{
			putc (c, stdout);
			column++;
		}
		c = getc (stdin);
	}
	return;
}


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
		"l:w:",
		PUTOPTV_S_FUNNEL,
		"copy one or more file headers to stdout",
		"l n\tdisplay line count is (n) [" LITERAL (VT_LINES) "]",
		"w n\tdisplay line width is (n) [" LITERAL (VT_LIMIT) "]",
		(char const *)(0)
	};
	unsigned lines = VT_LINES;
	unsigned width = VT_LIMIT;
	signed c;
	getviewport (&lines, &width);
	lines--;
	lines--;
	width--;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'l':
			lines = uintspec (optarg, 1, SHRT_MAX);
			break;
		case 'w':
			width = uintspec (optarg, 1, SHRT_MAX);
			break;
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (!argc) 
	{
		function (lines, width);
	}
	while ((argc) && (* argv)) 
	{
		if (efreopen (* argv, "rb", stdin)) 
		{
			function (lines, width);
		}
		argc--;
		argv++;
	}
	exit (0);
}

