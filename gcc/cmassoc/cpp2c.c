/*====================================================================*
 *
 *   cpp2c.c - convert C++ comments to C comments;
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

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../chrlib/chrlib.h"
#include "../clang/clang.h"
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
#include "../tidy/fortran.c"
#include "../tidy/literal.c"
#include "../tidy/escaped.c"
#include "../tidy/keep.c"
#endif

/*====================================================================*
 *   program vaiables;
 *--------------------------------------------------------------------*/

unsigned lineno = 0;

/*====================================================================*
 *
 *   signed comment (signed c) 
 *
 *   read stdin and write stdout; process a C language comment block; 
 *   return the character that follows the comment;
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

signed comment (signed c) 

{
	if (c != EOF) 
	{
		c = keep (c);
	}
	if (c == '/') 
	{
		putc ('*', stdout);
		do 
		{
			do 
			{
				c = getc (stdin);
			}
			while (c == '/');
			if ((c != '\n') && (c != EOF)) 
			{
				putc ('\n', stdout);
				putc (' ', stdout);
				putc ('*', stdout);
				do 
				{
					c = keep (c);
				}
				while ((c != '\n') && (c != EOF));
			}
			do 
			{
				c = getc (stdin);
			}
			while (c == '\n');
		}
		while (c == '/');
		putc ('\n', stdout);
		putc (' ', stdout);
		putc ('*', stdout);
		putc ('/', stdout);
		putc ('\n', stdout);
		return (c);
	}
	if (c == '*') 
	{
		while ((c != '/') && (c != EOF)) 
		{
			while ((c != '*') && (c != EOF)) 
			{
				c = keep (c);
			}
			c = keep (c);
			while (c == '*') 
			{
				c = getc (stdin);
			}
		}
		if (c != EOF) 
		{
			c = keep (c);
		}
		return (c);
	}
	return (c);
}


/*====================================================================*
 *
 *   void function (signed c, flag_t flags);
 *
 *   read stdin and write stdout; intercept and process C Language
 *   style comments that start with double slash or appear between
 *   inverted slash/asterisk character pairs;  
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (signed c, flag_t flags) 

{
	while (c != EOF) 
	{
		if (isspace (c)) 
		{
			do 
			{
				c = keep (c);
			}
			while (isspace (c));
			continue;
		}
		if (isalpha (c)) 
		{
			do 
			{
				c = keep (c);
			}
			while (isalnum (c) || (c == '_'));
			continue;
		}
		if (isdigit (c)) 
		{
			do 
			{
				c = keep (c);
			}
			while (isdigit (c) || (c == '.'));
			continue;
		}
		if (c == '#') 
		{
			c = fortran (c);
			continue;
		}
		if (c == '/') 
		{
			c = comment (c);
			continue;
		}
		if (isquote (c)) 
		{
			c = literal (c, c);
			continue;
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
		"",
		PUTOPTV_S_FILTER,
		"convert C++ comments to C comments",
		(char const *) (0)
	};
	flag_t flags = (flag_t)(0);
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (!argc) 
	{
		c = getc (stdin);
		function (c, flags);
	}
	while ((argc) && (* argv)) 
	{
		if (vfopen (* argv)) 
		{
			c = getc (stdin);
			function (c, flags);
		}
		argc--;
		argv++;
	}
	exit (0);
}

