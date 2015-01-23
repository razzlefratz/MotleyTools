/*====================================================================*
 *
 *   pad.c - file pad program;
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
#include <string.h>
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

#define BLOCKSIZE 1

/*====================================================================*
 *
 *   signed function (signed blocksize);
 *
 *   copy file using fixed blocksize so that the output is always a
 *   multiple of the blocksize;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static signed function (signed blocksize)

{
	void * memory = malloc (blocksize);
	if (memory)
	{
		memset (memory, 0, blocksize);
		while (read (STDIN_FILENO, memory, blocksize) > 0)
		{
			write (STDOUT_FILENO, memory, blocksize);
			memset (memory, 0, blocksize);
		}
		free (memory);
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
		"copy one or more files to stdout",
		PUTOPTV_S_FUNNEL,
		"b:u",
		"b n\tblock size is (n) bytes [" LITERAL (BLOCKSIZE) "]",
		"u\tunbuffered copy",
		(char const *) (0)
	};
	signed blocksize = BLOCKSIZE;
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'b':
			blocksize = uintspec (optarg, 1, SHRT_MAX);
			break;
		case 'u':
			blocksize = 1;
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		function (blocksize);
	}
	while ((argc) && (* argv))
	{
		if (efreopen (* argv, "rb", stdin))
		{
			function (blocksize);
		}
		argc--;
		argv++;
	}
	exit (0);
}

