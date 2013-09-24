/*====================================================================*
 *
 *   rexp.c - regular expression test and demo program; 
 *
 *   parse argv[1] as a regular expression and compare any remaining
 *   arguments to it; display a description and report match results;
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
#include <string.h>
#include <stddef.h>
#include <ctype.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../chrlib/chrlib.h"
#include "../regex/regex.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/emalloc.c"
#include "../tools/todigit.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../regex/regexmake.c"
#include "../regex/regexspan.c"
#include "../regex/regexcomp.c"
#include "../regex/regexfree.c"
#include "../regex/regexshow.c"
#endif

#ifndef MAKEFILE
#include "../chrlib/charset.c"
#include "../chrlib/chruesc.c"
#endif

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv [])

{
	static char const * optv [] = 
	{
		"e:",
		"literal [literal] [...]",
		"compare example strings to a regular expression and report each outcome",
		"e\tthe regular expression",
		(char const *) (0)
	};
	regexp * pattern = (regexp *) (0);
	char prefix [TEXTLINE_MAX];
	char const * sp;
	char const * cp;
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'e':
			pattern = regexmake (optarg);
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	while ((argc) && (* argv))
	{
		sp = regexspan (pattern, * argv);
		if (! sp)
		{
			printf ("[] [%s]\n", * argv);
		}
		else if (! * sp)
		{
			printf ("[%s] []\n", * argv);
		}
		else 
		{
			for (cp = * argv; cp < sp; cp++)
			{
				prefix [cp - * argv] = * cp;
			}
			prefix [cp - * argv] = (char) (0);
			printf ("[%s] [%s]\n", prefix, sp);
		}
		argc--;
		argv++;
	}

#if 0

	regexshow (pattern);

#endif

	regexfree (pattern);
	exit (0);
}

