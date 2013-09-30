/*====================================================================*
 *
 *   detab.c - replace tab characters with spaces;
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
#include <ctype.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../tools/tabs.h"
#include "../files/files.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/emalloc.c"
#include "../tools/error.c"
#include "../tools/tabspec.c"
#include "../tools/tabs.c"
#endif

#ifndef MAKEFILE
#include "../files/vfopen.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#include "../files/match.c"
#endif

/*====================================================================*
 *
 *   void function (flag_t flag);
 *
 *   read from stdin and write to stdout; replace ht characters with
 *   spaces; use tabset() to define tabstops and tabcol() to lookup
 *   them up;
 *
 *   this is a modified version of the entab program from 'Software
 *   Tools' by Kernighan and Plaugher;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (flag_t flags)

{
	int col = 0;
	int c;
	while ((c = getc (stdin)) != EOF)
	{
		if (isprint (c))
		{
			putc (c, stdout);
			col++;
			continue;
		}
		if (c == '\b')
		{
			if (col > 0)
			{
				col--;
			}
			putc (c, stdout);
			continue;
		}
		if (c == '\t')
		{
			while (tabcol (++ col) == false)
			{
				putc (' ', stdout);
			}
			putc (' ', stdout);
			continue;
		}
		if ((c == '\r') || (c == '\n') || (c == '\t'))
		{
			putc (c, stdout);
			col = 0;
			continue;
		}
		putc (c, stdout);
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
		"t:",
		PUTOPTV_S_FILTER,
		"replace horizontal tabs with equivalent number of spaces",
		"t n.m\tset tabs in column (n) and intervals (m) ",
		(char const *) (0)
	};
	flag_t flags = (flag_t) (0);
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 't':
			tabspec (optarg);
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		function (flags);
	}
	while ((argc) && (* argv))
	{
		if (vfopen (* argv))
		{
			function (flags);
		}
		argc--;
		argv++;
	}
	exit (0);
}

