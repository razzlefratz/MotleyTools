/*====================================================================*
 *
 *   filesize.c -
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *%  Packaged as cmassoc-tools-1.3.11 by cmaier@cmassoc.net;
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#endif

#ifndef MAKEFILE
#include "../files/filepart.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define SCALE_MAX 1000000
#define WIDTH_MAX 64
#define DIGIT_MAX 16
#define SCALE 1000
#define WIDTH 12
#define DIGIT 8
#define BAR '#'

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
		"display files sizes",
		"file [file] [...]",
		"c:d:s:",
		"d n\tdisplay (n) digits [" LITERAL (DIGIT) "]",
		"s n\tscale size by (n) [" LITERAL (SCALE) "]",
		"c n\tdisplay (n) characters [" LITERAL (SCALE) "]",
		(char const *) (0)
	};
	struct stat statinfo;
	signed width = WIDTH;
	signed digit = DIGIT;
	signed scale = SCALE;
	off_t value;
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'c':
			width = uintspec (optarg, 1, WIDTH_MAX);
			break;
		case 'd':
			digit = uintspec (optarg, 1, DIGIT_MAX);
			break;
		case 's':
			scale = uintspec (optarg, 1, SCALE_MAX);
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	while ((argc) && (* argv))
	{
		if (lstat (* argv, & statinfo))
		{
			error (0, errno, "Can't stat %s", * argv);
		}
		else 
		{
			printf ("%*.*s ", width, width, * argv);

#ifdef __APPLE__

			printf ("%*llu ", digit, statinfo.st_size);

#else

			printf ("%*lu ", digit, statinfo.st_size);

#endif

			for (value = statinfo.st_size; value > (scale >> 1); value -= scale)
			{
				putc ('#', stdout);
			}
			putc ('\n', stdout);
		}
		argc--;
		argv++;
	}
	exit (0);
}

