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
 *
 *   void function (size_t lower, size_t upper, flag_t flags);
 *
 *   discard text prior to column lower and after column upper on
 *   each line of a text file;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function(size_t lower, size_t upper, flag_t flags)

{
	size_t column;
	signed c;
	for (column = 1; (c = getc(stdin)) != EOF; column++)
	{
		if (c == '\n')
		{
			putc (c, stdout);
			column = 0;
			continue;
		}
		if (lower < upper)
		{
			if ((column < lower) || (column > upper))
			{
				continue;
			}
		}
		if (lower > upper)
		{
			if ((column < lower) && (column > upper))
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

int main(int argc, char const * argv[])

{
	static char const * optv[] = 
	{
		"a:b:",
		PUTOPTV_S_FILTER,
		"discard character columns",
		"a n\tafter column (n)",
		"b n\tbefore column (n)",
		(char const *)(0)
	};
	flag_t flags = (flag_t)(0);
	unsigned lower = 0;
	unsigned upper = 0;
	signed c;
	while (~ (c = getoptv(argc, argv, optv)))
	{
		switch (c)
		{
		case 'a':
			upper = uintspec(optarg, 0, USHRT_MAX);
			break;
		case 'b':
			lower = uintspec(optarg, 0, USHRT_MAX);
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		function (lower, upper, flags);
	}
	while ((argc) && (* argv))
	{
		if (vfopen(* argv))
		{
			function (lower, upper, flags);
		}
		argc--;
		argv++;
	}
	exit (0);
}

