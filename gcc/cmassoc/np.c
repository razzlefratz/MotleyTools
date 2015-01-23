/*====================================================================*
 *
 *   np.c - new paragraph
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
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"

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
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#include "../files/makepath.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define NP_VERBOSE (1 << 0)
#define NP_SILENCE (1 << 1)

/*====================================================================*
 *
 *   void function (char const * prefix, char const * string);
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (char const * prefix, char const * string)

{
	char const * pp;
	char const * sp;
	signed c;
	while ((c = getc (stdin)) != EOF)
	{
		for (pp = prefix; c == * pp; pp++)
		{
			c = getc (stdin);
		}
		if (* pp)
		{
			sp = prefix;
			while (sp < pp)
			{
				putc (* sp++, stdout);
			}
			while (nobreak (c))
			{
				putc (c, stdout);
				c = getc (stdin);
			}
		}
		else 
		{
			sp = string;
			while (* sp)
			{
				putc (* sp++, stdout);

#if 1

				if (* sp == '\\')
				{
					sp++;
				}

#endif

			}
			while (nobreak (c))
			{
				c = getc (stdin);
			}
		}
		if (c != EOF)
		{
			putc (c, stdout);
		}
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
		"new paragraph",
		PUTOPTV_S_FILTER,
		"p:s:",
		"p s\tparagraph prefix",
		"s s\tparagraph string",
		(char const *) (0)
	};
	char const * prefix = "";
	char const * string = "";
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'p':
			prefix = optarg;
			break;
		case 's':
			string = optarg;
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! prefix || ! * prefix)
	{
		error (1, ECANCELED, "paragraph prefix is empty");
	}
	if (! string || ! * string)
	{
		error (1, ECANCELED, "paragraph string is empty");
	}
	if (! argc)
	{
		function (prefix, string);
	}
	while ((argc) && (* argv))
	{
		if (vfopen (* argv))
		{
			function (prefix, string);
		}
		argc--;
		argv++;
	}
	exit (0);
}

