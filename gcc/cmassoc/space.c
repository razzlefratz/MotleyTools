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
#include "../tidy/literal.c"
#include "../tidy/escaped.c"
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

#define SPACE_DEFAULT ' '
#define SPACE_NOTHING '\0'
#define SPACE_NEWLINE '\t'

/*====================================================================*
 *
 *   void function (char newline);
 *
 *   read stdin and write stdout; replace leading spaces and tabs 
 *   with character newline unless newline is NUL; replace embedded 
 *   spaces and tabs with one space; discard trailing spaces and tabs;
 *
 *   write literal strings, enclosed in quotes or apostrophes, as 
 *   as read; ignore escaped newlines as line terminators;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (char newline) 

{
	signed c = getc (stdin);
	while (c != EOF) 
	{
		if (isblank (c)) 
		{
			do 
			{
				c = getc (stdin);
			}
			while (isblank (c));
			if (nobreak (c)) 
			{
				if (newline) 
				{
					putc (newline, stdout);
				}
			}
		}
		while (nobreak (c)) 
		{
			if (c == '#') 
			{
				do 
				{
					c = keep (c);
				}
				while (nobreak (c));
				continue;
			}
			if (isquote (c)) 
			{
				c = literal (c);
				continue;
			}
			if (isblank (c)) 
			{
				do 
				{
					c = getc (stdin);
				}
				while (isblank (c));
				if (nobreak (c)) 
				{
					putc (' ', stdout);
				}
				continue;
			}
			c = keep (c);
		}
		c = getc (stdin);
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
		"c:nst",
		PUTOPTV_S_FILTER,
		"white space manager",
		"c c\tindent character is c",
		"n\tindent character is nothing [" LITERAL (SPACE_NOTHING) "]",
		"s\tindent character is space [" LITERAL (SPACE_DEFAULT) "]",
		"t\tindent character is tab [" LITERAL (SPACE_NEWLINE) "]",
		(char *) (0)
	};
	char newline = SPACE_NEWLINE;
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'c':
			newline = * struesc ((char *) (optarg));
			break;
		case 'n':
			newline = SPACE_NOTHING;
			break;
		case 's':
			newline = SPACE_DEFAULT;
			break;
		case 't':
			newline = SPACE_NEWLINE;
			break;
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (!argc) 
	{
		function (newline);
	}
	while ((argc) && (* argv)) 
	{
		if (vfopen (* argv)) 
		{
			function (newline);
		}
		argc--;
		argv++;
	}
	exit (0);
}

