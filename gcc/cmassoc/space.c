/*====================================================================*
 *
 *   space.c - white space minimizer;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
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

#define SPACE_NEWLINE '\t'
#define SPACE_ENDLINE '\n'

/*====================================================================*
 *
 *   void function (char newline, char endline);
 *
 *   read stdin and write stdout; replace leading spaces and tabs 
 *   with character newline unless newline is NUL; replace embedded 
 *   spaces and tabs with one space; discard trailing spaces and tabs;
 *
 *   write literal strings, enclosed in quotes or apostrophes, as 
 *   as read; ignore escaped newlines as line terminators;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void function (char newline, char endline) 

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
				c = literal (c, c);
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
		if (endline) 
		{
			putc (endline, stdout);
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
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"c:e:nst",
		PUTOPTV_S_FILTER,
		"white space minimizer",
		"c c\tindent character is c",
		"e c\tend of line character is c",
		"n\tindent character is nothing",
		"s\tindent character is space [\' \']",
		"t\tindent character is tab [\'\\t\']",
		(char *) (0)
	};
	char newline = SPACE_NEWLINE;
	char endline = SPACE_ENDLINE;
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'c':
			newline = *struesc ((char *) (optarg));
			break;
		case 'e':
			endline = *struesc ((char *) (optarg));
			break;
		case 'n':
			newline = (char) (0);
			break;
		case 's':
			newline = ' ';
			break;
		case 't':
			newline = '\t';
			break;
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (!argc) 
	{
		function (newline, endline);
	}
	while ((argc) && (* argv)) 
	{
		if (vfopen (* argv)) 
		{
			function (newline, endline);
		}
		argc--;
		argv++;
	}
	exit (0);
}

