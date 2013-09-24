/*====================================================================*
 *
 *   bin2hex.c - binary to hexadecimal file concatenate;
 *
 *   print one or more files on stdout in hexadecimal format; if no 
 *   files are specified on the command line then read from stdin;
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
#include "../tools/efreopen.c"
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#include "../tools/error.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define BIN2HEX_COLUMN 16

/*====================================================================*
 *
 *   signed function (signed extent, unsigned column);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (size_t column)

{
	byte byte;
	size_t offset;
	for (offset = 0; read (STDIN_FILENO, & byte, sizeof (byte)) > 0; offset++)
	{
		write (STDOUT_FILENO, & DIGITS_HEX [(byte >> 4) & 0x0F], sizeof (char));
		write (STDOUT_FILENO, & DIGITS_HEX [(byte >> 0) & 0x0F], sizeof (char));
		if (offset && column)
		{
			write (STDOUT_FILENO, offset % column? " ": "\n", sizeof (char));
		}
	}
	write (STDOUT_FILENO, "\n", sizeof (char));
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
		"w:",
		PUTOPTV_S_FUNNEL,
		"binary to hexadecimal file concatenate",
		"w n\tcolumn wrap is (n) octets [" LITERAL (BIN2HEX_COLUMN) "]",
		(char const *)(0)
	};
	size_t column = BIN2HEX_COLUMN;
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'w':
			column = uintspec (optarg, 0, UCHAR_MAX);
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		function (column);
	}
	while ((argc) && (* argv))
	{
		if (efreopen (* argv, "rb", stdin))
		{
			function (column);
		}
		argc--;
		argv++;
	}
	exit (0);
}

