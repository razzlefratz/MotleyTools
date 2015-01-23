/*====================================================================*
 *
 *   dmp2hex.c - convert hex dump file to plain hex file;
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
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#include "../tools/error.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define WIDTH 48

/*====================================================================*
 *
 *   void function (char const * source, size_t prior, size_t after);
 *
 *   discard text prior to column prior and after column after on
 *   each line of a text file; convert remaining text to binary;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static signed function (signed c, unsigned width)

{
	while (c != EOF)
	{
		unsigned count;
		while (isblank (c))
		{
			c = getc (stdin);
		}
		while (isxdigit (c))
		{
			c = getc (stdin);
		}
		while (isblank (c))
		{
			c = getc (stdin);
		}
		if (nobreak (c))
		{
			for (count = 0; count < width; count++)
			{
				putc (c, stdout);
				c = getc (stdin);
			}
		}
		while (nobreak (c))
		{
			c = getc (stdin);
		}
		if (c != EOF)
		{
			putc (c, stdout);
			c = getc (stdin);
		}
	}
	return (c);
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
		"convert hex dump files to hex file",
		PUTOPTV_S_FUNNEL,
		"w:",
		"w n\twidth is (n) characters [" LITERAL (WIDTH) "]",
		(char const *) (0)
	};
	unsigned width = WIDTH;
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'w':
			width = (unsigned) (uintspec(optarg, 2, 256));
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		function (getc (stdin), width);
	}
	while ((argc) && (* argv))
	{
		if (! freopen (* argv, "rb", stdin))
		{
			error (1, errno, "%s", * argv);
		}
		function (getc (stdin), width);
		argc--;
		argv++;
	}
	return (0);
}

