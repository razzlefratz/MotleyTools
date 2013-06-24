/*====================================================================*
 *
 *   cbrief.c - remove C Language comments; 
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
#include "../tidy/tidy.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#endif

#ifndef MAKEFILE
#include "../files/vfopen.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#endif

#ifndef MAKEFILE
#include "../tidy/literal.c"
#include "../tidy/nocomment.c"
#include "../tidy/noliteral.c"
#include "../tidy/noescaped.c"
#include "../tidy/escaped.c"
#include "../tidy/keep.c"
#endif

/*====================================================================*
 *
 *   void comment (int c);
 *
 *   tidy.h
 *
 *   read stdin and write stdout; pass C style comment block;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed comment (signed c) 

{
	c = getc (stdin);
	if (c == '/') 
	{
		putc ('/', stdout);
		do 
		{
			c = keep (c);
		}
		while ((c != '\n') && (c != EOF));
		putc ('\n', stdout);
		c = keep (c);
		return (c);
	}
	if (c == '*') 
	{
		putc ('/', stdout);
		c = keep (c);
		while ((c != '/') && (c != EOF)) 
		{
			while ((c != '*') && (c != EOF)) 
			{
				c = keep (c);
			}
			c = keep (c);
		}
		c = keep (c);
		putc ('\n', stdout);
		return (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   void exclude (void);
 *
 *   read stdin and write stdout; intercept and exclude C Language
 *   style comments that start with double slash or appear between
 *   inverted slash/asterisk character pairs;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void exclude (void) 

{
	signed c = getc (stdin);
	while (c != EOF) 
	{
		if (c == '/') 
		{
			c = nocomment (c);
			continue;
		}
		if (isquote (c)) 
		{
			c = literal (c);
			continue;
		}
		c = keep (c);
	}
	return;
}

/*====================================================================*
 *
 *   void include (void);
 *
 *   read stdin and write stdout; intercept and include C Language
 *   style comments that start with double slash or appear between
 *   inverted slash/asterisk character pairs;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void include (void) 

{
	signed c = getc (stdin);
	while (c != EOF) 
	{
		if (c == '/') 
		{
			c = getc (stdin);
			if (c == '/') 
			{
				putc ('/', stdout);
				do 
				{
					c = keep (c);
				}
				while ((c != '\n') && (c != EOF));
				putc ('\n', stdout);
				c = keep (c);
				continue;
			}
			if (c == '*') 
			{
				putc ('/', stdout);
				c = keep (c);
				while ((c != '/') && (c != EOF)) 
				{
					while ((c != '*') && (c != EOF)) 
					{
						c = keep (c);
					}
					c = keep (c);
				}
				c = keep (c);
				putc ('\n', stdout);
				continue;
			}
		}
		if (isquote (c)) 
		{
			c = noliteral (c);
			continue;
		}
		c = getc (stdin);
	}
	return;
}

/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
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
		"v",
		PUTOPTV_S_FILTER,
		"remove C/C++ language comments",
		"v\tdiscard source code",
		(char const *) (0)
	};
	void (* function) (void) = exclude;
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'v':
			function = include;
			break;
		default:
			break;
		}
	}
	argc-= optind;
	argv+= optind;
	if (!argc) 
	{
		function ();
	}
	while ((argc) && (* argv)) 
	{
		if (vfopen (* argv)) 
		{
			function ();
		}
		argv++;
		argc--;
	}
	return (0);
}

