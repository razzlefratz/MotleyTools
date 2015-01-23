/*====================================================================*
 *
 *   sbrief.c - remove comments, minimize space and concatenate
 *   continuation lines;
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
#include <string.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../files/files.h"
#include "../tidy/tidy.h"

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

#ifndef MAKEFILE
#include "../tidy/consume.c"
#include "../tidy/literal.c"
#include "../tidy/escaped.c"
#include "../tidy/span.c"
#include "../tidy/keep.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define SBRIEF_C_COMMENT '#'

/*====================================================================*
 *
 *   signed noop (signed c);
 *
 *   do nothing; return character argument;
 *
 *--------------------------------------------------------------------*/

static signed join (signed c)

{
	span (c, '\\', '\n');
	return (c);
}

static signed noop (signed c)

{
	return (c);
}

/*====================================================================*
 *
 *   void function (signed comment, signed tab, flag_t flags);
 *
 *   read stdin and write stdout; discard comment lines, concatenate
 *   continuation lines and replace spaces and tabs with one space;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (signed comment, signed escape (signed))

{
	signed c = getc (stdin);
	while (c != EOF)
	{
		if (isblank (c))
		{
			do 
			{
				c = getc (stdin);
			}
			while (isblank (c));
			if (nobreak (c) && (c != comment))
			{
				putc ('\t', stdout);
			}
		}
		while (nobreak (c))
		{
			if (c == comment)
			{
				c = consume ('\n');
				continue;
			}
			if (isblank (c))
			{
				do 
				{
					c = getc (stdin);
					c = escape (c);
				}
				while (isblank (c));
				if (nobreak (c))
				{
					putc (' ', stdout);
				}
				continue;
			}
			if (isquote (c))
			{
				c = literal (c);
				continue;
			}
			c = escape (c);
			c = keep (c);
		}
		c = keep (c);
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
		"remove comments, concatenate continuation lines and condense space",
		PUTOPTV_S_FILTER,
		"c:m",
		"c c\tcomment character is (c) [" LITERAL (SBRIEF_C_COMMENT) "]",
		"m\tmerge continuation lines",
		(char const *) (0)
	};
	signed (* escape) (signed) = noop;
	signed comment = SBRIEF_C_COMMENT;
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'c':
			comment = * optarg;
			break;
		case 'm':
			escape = join;
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		function (comment, escape);
	}
	while ((argc) && (* argv))
	{
		if (vfopen (* argv))
		{
			function (comment, escape);
		}
		argc--;
		argv++;
	}
	exit (0);
}

