/*====================================================================*
 *
 *   dash1.c - place double-dashed arguments on single lines;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../files/files.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../files/vfopen.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#endif

/*====================================================================*
 *
 *   void function (flag_t flags);
 *
 *   read from ifp and write to ofp; detect double-dashed arguments
 *   and move each one to a new line; replace leading whitespace on
 *   each line with one horizontal tab character;
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (flag_t flags)

{
	signed c;
	signed o;
	while ((c = getc (stdin)) != EOF)
	{
		switch (c)
		{
		case '#':
			do 
			{
				putc (c, stdout);
				c = getc (stdin);
			}
			while (nobreak (c));
			putc ('\n', stdout);
			break;
		case '\\':
			c = getc (stdin);
			if (c == '\n')
			{
				do 
				{
					c = getc (stdin);
				}
				while (isblank (c));
				ungetc (c, stdin);
			}
			else if (c == EOF)
			{
				putc ('\\', stdout);
				putc ('\n', stdout);
			}
			else 
			{
				putc ('\\', stdout);
				putc (c, stdout);
			}
			break;
		case '\"':
		case '\'':
			o = c;
			do 
			{
				putc (c, stdout);
				o = getc (stdin);
				if (c == '\\')
				{
					putc (c, stdout);
					c = getc (stdin);
					putc (c, stdout);
					c = getc (stdin);
				}
			}
			while ((c != EOF) && (c != o));
			putc (o, stdout);
			break;
		case '-':
			c = getc (stdin);
			if (c == '-')
			{
				putc ('\\', stdout);
				putc ('\n', stdout);
				putc ('\t', stdout);
				putc ('-', stdout);
			}
			else 
			{
				ungetc (c, stdin);
			}
			putc ('-', stdout);
			break;
		default: 
			putc (c, stdout);
			break;
		}
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
		"h",
		PUTOPTV_S_FILTER,
		"break double-dashed arguments out onto individual lines;",
		(char *) (0)
	};
	flag_t flags = (flag_t) (0);
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'h':
			putoptv (optv);
			exit (0);
		case ':':
			exit (1);
		case '?':
			exit (1);
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

