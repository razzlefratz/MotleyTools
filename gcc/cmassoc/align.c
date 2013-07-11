/*====================================================================*
 *
 *   align.c - character to column program;
 *
 *   This program aligns the specified character to a specified column
 *   on each line of a text file. The first occurance of the character,
 *   within a selected column range, is forced to the alignment column
 *   if possible. Preceding text is not altered. Trailing text is moved
 *   as required by alignment.
 *
 *   This program has specific application in aligning computer language
 *   source code comment fields to a specific column. It also has other
 *   occasional uses.
 *
 *   $ align [/Cc /Tn /Rn /Ln] [<infile] [>outfile]
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
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../strlib/strlib.h"
#include "../chrlib/chrlib.h"

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../files/vfopen.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#endif

#ifndef MAKEFILE
#include "../chrlib/chrindex.c"
#include "../chrlib/chruesc.c"
#endif

#ifndef MAKEFILE
#include "../strlib/struesc.c"
#endif

/*====================================================================*
 *
 *   void function (unsigned minimum, unsigned maximum, unsigned column, char cc);
 *
 *   align the first occurance of character cc, found inside the column 
 *   range bounded by minmum and maximum, to a specific column.
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (unsigned minimum, unsigned maximum, unsigned column, char cc) 

{ 
	unsigned prev = 1; 
	unsigned next = 1; 
	signed c = getc (stdin); 
	while (c != EOF) 
	{ 
		if (c == '\n') 
		{ 
			putc (c, stdout); 
			c = getc (stdin); 
			prev = next = 1; 
			continue; 
		} 
		if ((c == cc) && (next > minimum) && (next < maximum)) 
		{ 
			next = column; 
			while (prev++ < next) 
			{ 
				putc (' ', stdout); 
			} 
			putc (c, stdout); 
			c = getc (stdin); 
			next++ ; 
			continue; 
		} 
		if (! isblank (c)) 
		{ 
			while (prev++ < next) 
			{ 
				putc (' ', stdout); 
			} 
			putc (c, stdout); 
			c = getc (stdin); 
			next++ ; 
			continue; 
		} 
		c = getc (stdin); 
		next++ ; 
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
		"a:b:c:t:", 
		PUTOPTV_S_FILTER, 
		"align character to column", 
		"a n\tafter column (n)", 
		"b n\tbefore column (n)", 
		"c c\talignment character (c)", 
		"t n\talignment column (n)", 
		(char const * )(0)
	}; 
	unsigned minimum = 0; 
	unsigned maximum = - 1; 
	unsigned character = 0; 
	unsigned column = 0; 
	signed c; 
	while ((c = getoptv (argc, argv, optv)) != - 1) 
	{ 
		switch (c) 
		{ 
		case 'a': 
			minimum = uintspec (optarg, 0, SHRT_MAX); 
			break; 
		case 'b': 
			maximum = uintspec (optarg, 0, SHRT_MAX); 
			break; 
		case 'c': 
			character = * optarg; 
			break; 
		case 't': 
			column = uintspec (optarg, 0, SHRT_MAX); 
			break; 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 
	if (! argc) 
	{ 
		function (minimum, maximum, column, character); 
	} 
	while ((argc) && (* argv)) 
	{ 
		if (vfopen (* argv)) 
		{ 
			function (minimum, maximum, column, character); 
		} 
		argc-- ; 
		argv++ ; 
	} 
	exit (0); 
} 

