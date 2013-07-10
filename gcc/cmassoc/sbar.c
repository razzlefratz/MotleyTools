/*====================================================================*
 *
 *   sbar.c - extend script comment bars;
 *
 *   force script comments to start in column 1 and extend comment
 *   bars to a specified length;
 *
 *   script comments start with a hash '#' and continue to the end
 *   of the line;
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
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../chrlib/chrlib.h"
#include "../linux/linux.h"
#include "../clang/clang.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#endif

#ifndef MAKEFILE
#include "../files/vfopen.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define SBAR_B_SHIFT    (1 << 0)
#define SBAR_B_EXECUTE  (1 << 1)

#define SBAR_WIDTH 70
#define SBAR_START '#'
#define SBAR_SPACE ' '

/*====================================================================*
 *
 *   void function (char start, char space, size_t length, flag_t flags);
 *
 *   read from stdin and write to stdout; shift script comment lines
 *   to column 1 and expand comment bars;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (signed start, signed space, size_t length, flag_t flags) 

{ 
	signed c; 
	size_t column; 
	while ((c = getc (stdin)) != EOF) 
	{ 
		if (flags & SBAR_B_SHIFT) 
		{ 
			for (column = 0; isblank (c); column++ ) 
			{ 
				if (c == '\t') 
				{ 
					column -= column % 8; 
					column += 8; 
				} 
				c = getc (stdin); 
			} 
		} 
		if (c == start) 
		{ 
			putc (start, stdout); 
			c = getc (stdin); 
			if ((c == space) || (c == CUPPER) || (c == CLOWER)) 
			{ 
				putc (space, stdout); 
				c = getc (stdin); 
				if ((c == CUPPER) || (c == CLOWER)) 
				{ 
					column = length; 
					while (column-- > 0) 
					{ 
						putc (c, stdout); 
					} 
					while (nobreak (c)) 
					{ 
						c = getc (stdin); 
					} 
				} 
			} 
		} 
		else if (flags & SBAR_B_SHIFT) 
		{ 
			while (column-- > 0) 
			{ 
				putc (' ', stdout); 
			} 
		} 
		while (nobreak (c)) 
		{ 
			putc (c, stdout); 
			c = getc (stdin); 
		} 
		putc ('\n', stdout); 
	} 
	return; 
} 

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{ 
	static char const * optv [] = 
	{ 
		"c:mw:x", 
		PUTOPTV_S_FILTER, 
		"extend script style comment bars", 
		"c c\tcomments start with character (c) [" LITERAL (FBAR_START) "]", 
		"m\tshift comments to left margin", 
		"w n\tmake bars n characters wide [" LITERAL (FBAR_WIDTH) "]", 
		"x\tmake files executable", 
		(char const * ) (0)
	}; 
	flag_t flags = (flag_t) (0); 
	size_t width = SBAR_WIDTH; 
	char start = SBAR_START; 
	char space = SBAR_SPACE; 
	signed c; 
	while ((c = getoptv (argc, argv, optv)) != - 1) 
	{ 
		switch (c) 
		{ 
		case 'c': 
			start = (char) (* optarg); 
			break; 
		case 'm': 
			_setbits (flags, SBAR_B_SHIFT); 
			break; 
		case 'x': 
			_setbits (flags, SBAR_B_EXECUTE); 
			break; 
		case 'w': 
			width = uintspec (optarg, 0, 255); 
			break; 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 
	if (! argc) 
	{ 
		function (start, space, width, flags); 
	} 
	while ((argc) && (* argv)) 
	{ 
		if (vfopen (* argv)) 
		{ 
			if (flags & SBAR_B_EXECUTE) 
			{ 
				if (chmod (* argv, 0755)) 
				{ 
					error (0, errno, "can't chmod %s", * argv); 
				} 
			} 
			function (start, space, width, flags); 
		} 
		argc-- ; 
		argv++ ; 
	} 
	exit (0); 
} 

