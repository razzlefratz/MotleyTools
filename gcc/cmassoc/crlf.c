/*====================================================================*
 *
 *   crlf.c - insert or remove <cr> and/or <lf> from file;
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
#include <string.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../files/files.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#endif

#ifndef MAKEFILE
#include "../files/vfopen.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#endif

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#define CRLF_B_CR 0x0001
#define CRLF_B_LF 0x0002

/*====================================================================*
 *
 *   void function (flag_t flags)
 *
 *   read from stdin and write to stdout; convert carriage return
 *   and line feed characters to UNIX, MAC or WINDOWS conventions;
 *
 *   UNIX uses a line feed, MAC uses a carriage return and WINDOWS
 *   uses both to terminate text lines in a file;
 *
 *   this function treats one cr or lf and cr/lf or lf/cr pairs as
 *   the line end; all occurances of any combination are replaced
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (flag_t flags)

{
	int c;
	while ((c = getc (stdin)) != EOF)
	{
		if (c == '\r')
		{
			if ((c = getc (stdin)) != '\n')
			{
				ungetc (c, stdin);
			}
			if (_anyset (flags, CRLF_B_CR))
			{
				putc ('\r', stdout);
			}
			if (_anyset (flags, CRLF_B_LF))
			{
				putc ('\n', stdout);
			}
			continue;
		}
		if (c == '\n')
		{
			if ((c = getc (stdin)) != '\r')
			{
				ungetc (c, stdin);
			}
			if (_anyset (flags, CRLF_B_CR))
			{
				putc ('\r', stdout);
			}
			if (_anyset (flags, CRLF_B_LF))
			{
				putc ('\n', stdout);
			}
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
		"change text line termination",
		PUTOPTV_S_FILTER,
		"asuw",
		"a\tto Apple computer format [" "'\\r'" "]",
		"s\tto stream format (no line breaks)",
		"u\tto standard Unix format [" "'\\n'" "]",
		"w\tto Microsoft Windows format [" "\"\\r\\n\"" "]",
		(char const *) (0)
	};
	flag_t flags = CRLF_B_LF;
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 's':
			_clrbits (flags, CRLF_B_CR);
			_clrbits (flags, CRLF_B_LF);
			break;
		case 'u':
			_clrbits (flags, CRLF_B_CR);
			_setbits (flags, CRLF_B_LF);
			break;
		case 'a':
			_setbits (flags, CRLF_B_CR);
			_clrbits (flags, CRLF_B_LF);
			break;
		case 'w':
			_setbits (flags, CRLF_B_CR);
			_setbits (flags, CRLF_B_LF);
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

