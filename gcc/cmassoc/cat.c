/*====================================================================*
 *
 *   cat.c - file concatenate program;
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
 *
 *   signed function (signed extent);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static signed function (signed extent)

{
	byte memory [extent];
	while ((extent = read (STDIN_FILENO, memory, extent)) > 0)
	{
		if (write (STDOUT_FILENO, memory, extent) < extent)
		{
			return (-1);
		}
	}
	return (0);
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
		"b:u",
		PUTOPTV_S_FUNNEL,
		"copy one or more files to stdout",
		"b n\tbuffer size is (n) bytes [" LITERAL (BUFFERSIZE) "]",
		"u\tunbuffered copy",
		(char const *) (0)
	};
	signed length = BUFFERSIZE;
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'b':
			length = uintspec (optarg, 1, SHRT_MAX);
			break;
		case 'u':
			length = 1;
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		function (length);
	}
	while ((argc) && (* argv))
	{
		if (efreopen (* argv, "rb", stdin))
		{
			function (length);
		}
		argc--;
		argv++;
	}
	exit (0);
}

