/*====================================================================*
 *
 *   space.c - white space minimizer;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../strlib/strlib.h"
#include "../chrlib/chrlib.h"
#include "../tidy/tidy.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#include "../tools/todigit.c"
#endif

#ifndef MAKEFILE
#include "../files/vfopen.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#endif

#ifndef MAKEFILE
#include "../tidy/consume.c"
#include "../tidy/compact.c"
#include "../tidy/literal.c"
#include "../tidy/escaped.c"
#include "../tidy/span.c"
#include "../tidy/keep.c"
#endif

#ifndef MAKEFILE
#include "../strlib/struesc.c"
#endif

#ifndef MAKEFILE
#include "../chrlib/chruesc.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define SPACE_C_COMMENT '#'

/*====================================================================*
 *
 *   void GNUMake (unsigned spaces, unsigned tabs);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void GNUMake (unsigned spaces, unsigned tabs) 

{
	if (tabs) 
	{
		do 
		{
			putc ('\t', stdout);
		}
		while (--tabs);
	}
	else if (spaces) 
	{
		putc ('\t', stdout);
	}
	return;
}


/*====================================================================*
 *
 *   void OpenWRT (unsigned spaces, unsigned tabs);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void OpenWRT (unsigned spaces, unsigned tabs) 

{
	if (tabs) 
	{
		do 
		{
			putc ('\t', stdout);
		}
		while (--tabs);
	}
	else if (spaces) 
	{
		putc (' ', stdout);
	}
	return;
}


/*====================================================================*
 *
 *   signed noop (signed c);
 *
 *   do nothing; return character argument;
 *
 *--------------------------------------------------------------------*/

static signed noop (signed c) 

{
	return (c);
}


/*====================================================================*
 *
 *   void function (void indent (signed, unsigned, unsigned), signed escape (signed));
 *
 *   read stdin and write stdout; replace leading spaces character o
 *   unless it is NUL; preserve leading tabs; replace embedded spaces
 *   and tabs with one space; discard trailing spaces and tabs; write
 *   literal strings, enclosed in quotes or apostrophes, as as read; 
 *   ignore and discard escaped newline characters;
 *
 *   this function is taylored for OpenWRT make files;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (signed comment, void indent (unsigned, unsigned), signed escape (signed)) 

{
	signed c = getc (stdin);
	while (c != EOF) 
	{
		if (isblank (c)) 
		{
			unsigned column = 0;
			unsigned spaces = 0;
			unsigned tabs = 0;
			while (isblank (c)) 
			{
				if (c == '\t') 
				{
					while (++column%8);
					tabs++;
				}
				else if (c == ' ') 
				{
					column++;
					spaces++;
				}
				c = getc (stdin);
			}
			if (nobreak (c) && (c != comment)) 
			{
				indent (spaces, tabs);
			}
		}
		while (nobreak (c)) 
		{
			if (c == comment) 
			{
				c = consume ('\n');
				continue;
			}
			if (isblank (c)) 
			{
				c = compact (' ', '\n');
				continue;
			}
			if (isquote (c)) 
			{
				c = literal (c);
				continue;
			}
			c = escape (c);
			c = keep (c);
		}
		c = keep (c);
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
		"c:jm",
		PUTOPTV_S_FILTER,
		"white space manager",
		"c c\tcomment character is (c) [" LITERAL (SPACE_C_COMMENT) "]",
		"g\tsuitable for GNU makefiles",
		"m\tmerge continuation lines",
		(char *) (0)
	};
	void (* indent) (unsigned, unsigned) = GNUMake;
	signed (* escape) (signed) = noop;
	signed comment = SPACE_C_COMMENT;
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'c':
			comment = * optarg;
			break;
		case 'g':
			indent = GNUMake;
			break;
		case 'm':
			escape = span;
			break;
		case 'w':
			indent = OpenWRT;
			break;
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (!argc) 
	{
		function (comment, indent, escape);
	}
	while ((argc) && (* argv)) 
	{
		if (vfopen (* argv)) 
		{
			function (comment, indent, escape);
		}
		argc--;
		argv++;
	}
	exit (0);
}


