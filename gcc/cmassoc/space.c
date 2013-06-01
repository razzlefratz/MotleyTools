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

#define CHR_NUL '\0'
#define CHR_HT '\t'
#define CHR_SP ' '

/*====================================================================*
 *
 *   void function (char newline, unsigned multiple);
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

void function (char o, unsigned multiple) 

{
	signed c = getc (stdin);
	while (c != EOF) 
	{
		if (isblank (c)) 
		{
			unsigned column = 0;
			unsigned spaces = 0;
			unsigned tabs = 0;
			do 
			{
				if (c == '\t') 
				{
					do 
					{
						column++;
					}
					while (column%8);
					tabs++;
				}
				else if (c == ' ') 
				{
					column++;
					spaces++;
				}
				c = getc (stdin);
			}
			while (isblank (c));
			if (nobreak (c)) 
			{
				if (o == '\t') 
				{
					tabs *= multiple;
					while (tabs--) 
					{
						putc (o, stdout);
					}
				}
				if (o == ' ') 
				{
					if ((spaces) || (tabs)) 
					{
						putc (o, stdout);
					}
				}
				if (o) 
				{
					putc (o, stdout);
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
		if (c != EOF) 
		{
			c =keep (c);
		}
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
		"c:mnst",
		PUTOPTV_S_FILTER,
		"white space minimizer",
		"c c\tindent character is c",
		"m\tpreserve multiple tabs",
		"n\tindent character is nothing [" LITERAL (CHR_NUL) "]",
		"s\tindent character is space [" LITERAL (CHR_HT) "]",
		"t\tindent character is tab [" LITERAL (CHR_HT) "]",
		(char *) (0)
	};
	char newline = CHR_HT;
	unsigned multiple = 0;
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'c':
			newline = * struesc ((char *) (optarg));
			break;
		case 'n':
			newline = CHR_NUL;
			break;
		case 's':
			newline = CHR_SP;
			break;
		case 'm':
			multiple = 1;
			break;
		case 't':
			newline = CHR_HT;
			break;
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (!argc) 
	{
		function (newline, multiple);
	}
	while ((argc) && (* argv)) 
	{
		if (vfopen (* argv)) 
		{
			function (newline, multiple);
		}
		argc--;
		argv++;
	}
	exit (0);
}

