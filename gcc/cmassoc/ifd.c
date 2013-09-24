/*====================================================================*
 *
 *   ifd.c - interface diagram generator
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
#include <ctype.h>
#include <errno.h>

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
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#include "../tools/error.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define IFD_ALTERNATE (1 << 0)

#define IFD_WIDTH 40
#define IFD_START 1
#define IFD_RIGHT 0

#define X "%02d"
#define Y "  "

#define IFD_LEFT0 "  " Y "  |  "
#define IFD_LEFT1 "  " Y "  |<-"
#define IFD_LEFT2 " [" X "] |<-"
#define IFD_LEFT3 "--| [" X "]"
#define IFD_LEFT4 "  " Y "  |--"

#define IFD_RIGHT0 "  |  " Y " "
#define IFD_RIGHT1 " [" X "] |--"
#define IFD_RIGHT2 "->|  " Y " "
#define IFD_RIGHT3 "->| [" X "]"
#define IFD_RIGHT4 "--|  " Y " "

/*====================================================================*
 *   
 *   void function (size_t width, flag_t flags);
 *   
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function(unsigned step, unsigned dir, unsigned width, flag_t flags)

{
	char name[_NAMESIZE];
	char * label;
	unsigned space;
	unsigned prior;
	unsigned extra;
	unsigned after;
	signed c;
	putc ('\n', stdout);
	while ((c = getc(stdin)) != EOF)
	{
		space = 0;
		label = name;
		prior = width;
		while (isspace(c))
		{
			if (c == '\n')
			{
				space++;
			}
			c = getc(stdin);
		}
		if (space)
		{
			unsigned count = width;
			printf (IFD_LEFT0);
			putc (' ', stdout);
			while (count--)
			{
				putc (' ', stdout);
			}
			putc (' ', stdout);
			printf (IFD_RIGHT0);
			putc ('\n', stdout);
		}
		while ((c != '\n') && (c != EOF))
		{
			if (prior)
			{
				prior--;
			}
			* label++ = (char) (c);
			c = getc(stdin);
		}
		* label = (char) (0);
		extra = prior % 2;
		after = prior / 2;
		prior = after;
		if (++ dir & 1)
		{
			printf (IFD_RIGHT1, step++);
			while (prior--)
			{
				putc ('-', stdout);
			}
			printf (" %s ", name);
			while (after--)
			{
				putc ('-', stdout);
			}
			while (extra--)
			{
				putc ('-', stdout);
			}
			if (_anyset(flags, IFD_ALTERNATE))
			{
				printf (IFD_RIGHT2);
			}
			else 
			{
				printf (IFD_RIGHT3, step++);
			}
		}
		else 
		{
			if (_anyset(flags, IFD_ALTERNATE))
			{
				printf (IFD_LEFT1);
			}
			else 
			{
				printf (IFD_LEFT2, ++ step);
			}
			while (prior--)
			{
				putc ('-', stdout);
			}
			printf (" %s ", name);
			while (after--)
			{
				putc ('-', stdout);
			}
			while (extra--)
			{
				putc ('-', stdout);
			}
			if (_anyset(flags, IFD_ALTERNATE))
			{
				printf (IFD_LEFT3, step++);
			}
			else 
			{
				printf (IFD_LEFT3, -- step);
				step++;
				step++;
			}
		}
		putc ('\n', stdout);
	}
	putc ('\n', stdout);
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

int main(int argc, char const * argv[])

{
	static char const * optv[] = 
	{
		"aln:rw:",
		PUTOPTV_S_FUNNEL,
		"interface diagram generator",
		"a\talternate steps left/right",
		"l\tstart direction is left",
		"r\tstart direction is right",
		"n n\tfirst step is (n) [" LITERAL(IFD_START) "]",
		"w n\twidth in characters [" LITERAL(IFD_WIDTH) "]",
		(char const *) (0)
	};
	flag_t flags = (flag_t) (0);
	size_t width = IFD_WIDTH;
	unsigned start = IFD_START;
	unsigned dir = IFD_RIGHT;
	signed c;
	while (~ (c = getoptv(argc, argv, optv)))
	{
		switch (c)
		{
		case 'a':
			_setbits (flags, IFD_ALTERNATE);
			break;
		case 'l':
			dir = 1;
			break;
		case 'n':
			start = uintspec(optarg, 1, 512);
			break;
		case 'r':
			dir = 0;
			break;
		case 'w':
			width = (size_t) (uintspec(optarg, 0, 1024));
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		function (start, dir, width, flags);
	}
	while ((argc) && (* argv))
	{
		if (! freopen(* argv, "rb+", stdin))
		{
			error (1, errno, "%s", * argv);
		}
		function (start, dir, width, flags);
		argc--;
		argv++;
	}
	return (0);
}

