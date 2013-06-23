/*====================================================================*
 *
 *   blank.c - remove blank lines from text file;
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
#include "../files/files.h"

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

#define BLANK_COUNT 1

/*====================================================================*
 *
 *   void func (const unsigned limit, flag_t flags)
 *
 *   read from stdin and write to stdout; remove trailing spaces from 
 *   output lines; limit sequences of blank lines;
 *
 *   length is the actual length of the current line without trailing
 *   space; column is the current character position; length advances
 *   to meet column when visible characters are read; they are reset
 *   to 0 when a newline is read;
 *
 *   limit is the maximum number of consecutive blank lines permitted;
 *   count is the number written; blank lines are discarded once count
 *   reaches limit; setting count to limit at the start suppresses any
 *   leading blank lines;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (const unsigned limit, flag_t flags) 

{
	size_t count = limit;
	size_t column = 0;
	size_t length = 0;
	signed c = getc (stdin);
	while (c != EOF) 
	{
		if (c == ' ') 
		{
			c = getc (stdin);
			length++;
			continue;
		}
#if 0

		if (c == '\t') 
		{
			length%= 8;
			length *= 8;
			length+= 8;
			c = getc (stdin);
			continue;
		}
#endif

		if (c == '\n') 
		{
			if (column) 
			{
				putc (c, stdout);
				count = 0;
			}
			else if (count < limit) 
			{
				putc (c, stdout);
				count++;
			}
			c = getc (stdin);
			column = 0;
			length = 0;
			continue;
		}
		while (column++ < length) 
		{
			putc (' ', stdout);
		}
		putc (c, stdout);
		c = getc (stdin);
		length++;
	}
	if (column) 
	{
		putc ('\n', stdout);
	}
	return;
}

/*====================================================================*
 *
 *   int main (int argc, char const * argv[]);
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
		"n:",
		PUTOPTV_S_FILTER,
		"minimize blank lines and eliminate trailing spaces",
		"n n\treduce consecutive blank lines to (n) lines [" LITERAL (BLANK_COUNT) "]",
		(char const *)(0)
	};
	flag_t flags = (flag_t)(0);
	size_t count = BLANK_COUNT;
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'n':
			count = uintspec (optarg, 0, SHRT_MAX);
			break;
		default:
			break;
		}
	}
	argc-= optind;
	argv+= optind;
	if (!argc) 
	{
		function (count, flags);
	}
	while ((argc) && (* argv)) 
	{
		if (vfopen (* argv)) 
		{
			function (count, flags);
		}
		argc--;
		argv++;
	}
	exit (1);
}

