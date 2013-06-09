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
#include "../tidy/conjoin.c"
#include "../tidy/literal.c"
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
 *   void GNUMake (signed o, unsigned spaces, unsigned tabs);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void GNUMake (signed o, unsigned spaces, unsigned tabs) 

{
	if (o) {
	if (tabs) 
	{
		do 
		{
			putc (o, stdout);
		}
		while (--tabs);
	}
	else if (spaces) 
	{
		putc (o, stdout);
	}}
	return;
}


/*====================================================================*
 *
 *   void OpenWRT (signed o, unsigned spaces, unsigned tabs);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void OpenWRT (signed o, unsigned spaces, unsigned tabs) 

{
	if (o) {
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
		putc (o, stdout);
	}}
	return;
}


/*====================================================================*
 *
 *   void function (signed o, void indent (signed, unsigned, unsigned);
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

void function (signed o, void indent (signed, unsigned, unsigned)) 

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
			if (nobreak (c)) 
			{
				indent (o, spaces, tabs);
			}
		}
		while (nobreak (c)) 
		{
			if (c == '#') 
			{
				do { c = getc (stdin); } while (nobreak (c));
				continue;
			}
			if (c == '\\') 
			{
				c = conjoin (c);
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
			c = keep (c);
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
		"c:MnostW",
		PUTOPTV_S_FILTER,
		"white space manager",
		"c c\tindent character is (c)",
		"M\tsuitable for GNU makefiles",
		"n\tindent is nothing [" LITERAL (CHR_NUL) "]",
		"s\tindent is one space [" LITERAL (CHR_SP) "]",
		"t\tindent is one tab [" LITERAL (CHR_HT) "]",
		"W\tsuitable for OpenWRT makefiles",
		(char *) (0)
	};
	void (* indent) (signed, unsigned, unsigned) = GNUMake;
	signed o = CHR_HT;
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'c':
			o = * struesc ((char *) (optarg));
			break;
		case 'M':
			indent = GNUMake;
			break;
		case 'n':
			o = CHR_NUL;
			break;
		case 's':
			o = CHR_SP;
			break;
		case 't':
			o = CHR_HT;
			break;
		case 'W':
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
		function (o, indent);
	}
	while ((argc) && (* argv)) 
	{
		if (vfopen (* argv)) 
		{
			function (o, indent);
		}
		argc--;
		argv++;
	}
	exit (0);
}

