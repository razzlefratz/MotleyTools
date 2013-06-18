/*====================================================================*
 *
 *   sbrief.c - remove comments, minimize space and concatenate 
 *   continuation lines;
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
#include <ctype.h>
#include <string.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../files/files.h"
#include "../tidy/tidy.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/error.c"
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

/*=*
 *   program constants;
 *-*/

#define SBRIEF_C_COMMENT '#'

/*====================================================================*
 *
 *   signed join (signed c);
 *
 *   discard escaped newline; return character argument or character
 *   following the newline;
 *
 *--------------------------------------------------------------------*/

static signed join (signed c) 

{
	if (c == '\\') 
	{
		signed o = getc (stdin);
		if (o == '\n') 
		{
			c = getc (stdin);
		}
		else
		{
			ungetc (o, stdin);
		}
	}
	return (c);
}


/*====================================================================*
 *
 *   signed pass (signed c);
 *
 *   do nothing; return character argument;
 *
 *--------------------------------------------------------------------*/

static signed pass (signed c) 

{
	return (c);
}


/*====================================================================*
 *
 *   void function (signed comment, signed tab, flag_t flags);
 *
 *   read stdin and write stdout; discard comment lines, concatenate
 *   continuation lines and replace spaces and tabs with one space;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (signed comment, signed escape (signed)) 

{
	signed c = (char) (0);
	while ((c = getc (stdin)) != EOF) 
	{
		if (isblank (c)) 
		{
			do 
			{
				c = getc (stdin);
			}
			while (isblank (c));
			if ((c != comment) && nobreak (c)) 
			{
				putc ('\t', stdout);
			}
		}
		if (c == comment) 
		{
			do 
			{
				c = getc (stdin);
			}
			while (nobreak (c));
			continue;
		}
		while (nobreak (c)) 
		{
			if (isblank (c)) 
			{
				do 
				{
					c = getc (stdin);
					c = escape (c);
				}
				while (isblank (c));
				if (nobreak (c)) 
				{
					putc (' ', stdout);
				}
				continue;
			}
			if (isquote (c)) 
			{
				c = literal (c);
				continue;
			}
			if (c == '\\') 
			{
				c = escape (c);
			}
			c = keep (c);
		}
		if (c != EOF)
		{
			putc (c, stdout);
		}
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
		"c:m",
		PUTOPTV_S_FILTER,
		"remove comments, concatenate continuation lines and condense space",
		"c c\tcomment character is (c) [" LITERAL (SBRIEF_C_COMMENT) "]",
		"m\tmerge continuation lines",
		(char const *) (0)
	};
	signed (* escape) (signed) = pass;
	signed comment = '#';
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'c':
			comment = *optarg;
			break;
		case 'm':
			escape = join;
			break;
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (!argc) 
	{
		function (comment, escape);
	}
	while ((argc) && (* argv)) 
	{
		if (vfopen (* argv)) 
		{
			function (comment, escape);
		}
		argc--;
		argv++;
	}
	exit (0);
}

