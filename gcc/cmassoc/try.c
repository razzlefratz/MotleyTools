/*====================================================================*
 *
 *   try.c - log and execute commands;
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
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/getoptv.h"
#include "../tools/putoptv.h"
#include "../tools/version.h"
#include "../tools/format.h"
#include "../tools/error.h"
#include "../tools/sizes.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE 
#include "../tools/console.c"
#include "../tools/breakout.c"
#endif

/*====================================================================*
 *
 *   int main (int argc, char * const argv []);
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
		"c:",
		"command [command] [...]",
		"Log and execute command sequences",
		"c s\tcomment text",
		(char const *) (0)
	};
	FILE * fp;
	char const * comment = (char const *)(0);
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'c':
			comment = optarg;
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	dup2 (STDOUT_FILENO, STDERR_FILENO);
	if ((comment) && (* comment))
	{
		breakout (comment, BARWIDTH_MAX);
	}
	while ((argc) && (* argv))
	{
		printf ("# %s\n", * argv);
		if ((fp = popen (* argv, "r")))
		{
			while ((c = getc (fp)) != EOF)
			{
				putc (c, stdout);
			}
		}
		printf ("\n");
		argc--;
		argv++;
	}
	exit (0);
}

