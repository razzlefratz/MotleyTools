/*====================================================================*
 *
 *   dmp2hex.c - convert hex dump to hex file;
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
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define TRIM_PRIOR 10
#define TRIM_AFTER 56

/*====================================================================*
 *
 *   void function (size_t prior, size_t after);
 *
 *   discard text prior to column prior and after column after on
 *   each line of a text file;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (size_t prior, size_t after)

{
	signed c;
	size_t column = 0;
	for (column++; (c = getc (stdin)) != EOF; column++)
	{
		if (c == '\n')
		{
			putc (c, stdout);
			column = 0;
			continue;
		}
		if (prior < after)
		{
			if ((column < prior) || (column > after))
			{
				continue;
			}
		}
		if (prior > after)
		{
			if ((column < prior) && (column > after))
			{
				continue;
			}
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
		"a:b:t",
		PUTOPTV_S_FUNNEL,
		"convert hex dump to hex file",
		"a n\tafter column (n) [" LITERAL (TRIM_PRIOR) "]",
		"b n\tbefore column (n) [" LITERAL (TRIM_AFTER) "]",
		"t\tconvert toolkit hex dump",
		(char const *) (0)
	};
	size_t prior = TRIM_PRIOR;
	size_t after = TRIM_AFTER;
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'a':
			after = (size_t)(uintspec (optarg, 0, 512)); 
			break;
		case 'b':
			prior = (size_t)(uintspec (optarg, 0, 512)); 
			break;
		case 't':
			prior = TRIM_PRIOR;
			after = TRIM_AFTER; 
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		function (prior, after);
	}
	while ((argc) && (* argv))
	{
		if (! freopen (* argv, "rb", stdin))
		{
			error (1, errno, "%s", * argv);
		}
		function (prior, after);
		argc--;
		argv++;
	}
	return (0);
}
