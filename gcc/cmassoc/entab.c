/*====================================================================*
 *
 *   entab.c - replace spaces with tab characters;
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
#include "../files/match.c"
#include "../files/vfopen.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#endif

/*====================================================================*
 *
 *   void function (flag_t flag);
 *
 *   read stdin and write stdout; replace spans of space characters
 *   with with tab characters; use tabset() to define tabstops and
 *   tabcol() to look them up;
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
	int next = 0;
	int prev = 0;
	int c;
	while ((c = getc (stdin)) != EOF)
	{
		if (isgraph (c))
		{
			while (prev++ < next)
			{
				putc (' ', stdout);
			}
			putc (c, stdout);
			next++;
			continue;
		}
		if (c == ' ')
		{
			if (tabcol (++ next) == true)
			{
				putc ('\t', stdout);
				prev = next;
			}
			continue;
		}
		if (c == '\b')
		{
			if (prev == next--)
			{
				prev--;
			}
			putc (c, stdout);
			continue;
		}
		if (c == '\t')
		{
			while (tabcol (++ next) == false);
			putc (c, stdout);
			prev = next;
			continue;
		}
		if ((c == '\r') || (c == '\n') || (c == '\f'))
		{
			while (prev++ < next)
			{
				putc (' ', stdout);
			}
			putc (c, stdout);
			prev = next = 0;
			continue;
		}
		putc (c, stdout);
	}
	return;
}

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv [])

{
	static char const * optv [] =
	{
		"replace spaces with horizontal tabs ",
		PUTOPTV_S_FILTER,
		"t:",
		"t n.m\tset tabs in column (n) and interval (m) ",
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

