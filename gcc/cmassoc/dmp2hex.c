/*====================================================================*
 *
 *   dump2hex.c - convert hex dump to hex file;
 *
 *   copy one or more files to stdout; if no files are specified 
 *   then copy stdin to stdout;
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
#include <limits.h>
#include <ctype.h>

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

/*====================================================================*
 *
 *   void function ();
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function()

{
	char c;
	while ((c = getc(stdin)) != EOF)
	{
		if (isxdigit(c))
		{
			while (isxdigit(c))
			{
				c = getc(stdin);
			}
			while (isblank(c) || isxdigit(c))
			{
				putc (c, stdout);
				c = getc(stdin);
			}
		}
		while (nobreak(c))
		{
			c = getc(stdin);
		}
		putc ('\n', stdout);
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

int main(int argc, char const * argv[])

{
	static char const * optv[] = 
	{
		"",
		PUTOPTV_S_FUNNEL,
		"hex dump to hex file converter",
		(char const *) (0)
	};
	signed c;
	while (~ (c = getoptv(argc, argv, optv)))
	{
		switch (c)
		{
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		function ();
	}
	while ((argc) && (* argv))
	{
		if (! freopen(* argv, "rb", stdin))
		{
			error (1, errno, "%s", * argv);
		}
		function ();
		argc--;
		argv++;
	}
	return (0);
}

