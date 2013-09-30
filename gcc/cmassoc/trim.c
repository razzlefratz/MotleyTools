/*====================================================================*
 *
 *   trim.c - discard character columns;
 *
 *   discard a range of columns from each line of a text file;
 *   characters occuring before one column and/or after another
 *   are discarded;
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
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#include "../files/vfopen.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define TRIM_PRIOR 0
#define TRIM_AFTER 0
#define TRIM_INDEX 10
#define TRIM_ASCII 56

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
 *   int main (int argc, char const * argv [])
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
		"a:b:x",
		PUTOPTV_S_FILTER,
		"discard character columns",
		"a n\tafter column (n) [" LITERAL (TRIM_PRIOR) "]",
		"b n\tbefore column (n) [" LITERAL (TRIM_AFTER) "]",
		"x\ttrim hex dump (-b" LITERAL (TRIM_INDEX) " -a" LITERAL (TRIM_ASCII) ")",
		(char const *) (0)
	};
	unsigned prior = TRIM_PRIOR;
	unsigned after = TRIM_AFTER;
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'a':
			after = uintspec (optarg, 0, USHRT_MAX);
			break;
		case 'b':
			prior = uintspec (optarg, 0, USHRT_MAX);
			break;
		case 'x':
			prior = TRIM_INDEX;
			after = TRIM_ASCII;
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
		if (vfopen (* argv))
		{
			function (prior, after);
		}
		argc--;
		argv++;
	}
	exit (0);
}

