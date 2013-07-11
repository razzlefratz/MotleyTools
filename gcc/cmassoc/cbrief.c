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
			c = getc (stdin); 
			if (c == '/') 
			{ 
				while ((c != '\n') && (c != EOF)) 
				{ 
					c = getc (stdin); 
				} 
				continue; 
			} 
			if (c == '*') 
			{ 
				while ((c != '/') && (c != EOF)) 
				{ 
					while ((c != '*') && (c != EOF)) 
					{ 
						c = getc (stdin); 
					} 
					c = getc (stdin); 
				} 
				c = getc (stdin); 
				continue; 
			} 
			putc ('/', stdout); 
			continue; 
		} 
		if (isquote (c)) 
		{ 
			signed quote = c; 
			putc (c, stdout); 
			c = getc (stdin); 
			while ((c != quote) && (c != EOF)) 
			{ 
				if (c == '\\') 
				{ 
					putc (c, stdout); 
					c = getc (stdin); 
				} 
				putc (c, stdout); 
				c = getc (stdin); 
			} 
			putc (c, stdout); 
			c = getc (stdin); 
		} 
		putc (c, stdout); 
		c = getc (stdin); 
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
				while ((c != '\n') && (c != EOF)) 
				{ 
					putc (c, stdout); 
					c = getc (stdin); 
				} 
				continue; 
			} 
			if (c == '*') 
			{ 
				putc ('/', stdout); 
				while ((c != '/') && (c != EOF)) 
				{ 
					while ((c != '*') && (c != EOF)) 
					{ 
						putc (c, stdout); 
						c = getc (stdin); 
					} 
					putc (c, stdout); 
					c = getc (stdin); 
				} 
				putc (c, stdout); 
				c = getc (stdin); 
				putc ('\n', stdout); 
				continue; 
			} 
		} 
		if (isquote (c)) 
		{ 
			signed quote = c; 
			c = getc (stdin); 
			while ((c != quote) && (c != EOF)) 
			{ 
				if (c == '\\') 
				{ 
					c = getc (stdin); 
				} 
				c = getc (stdin); 
			} 
			c = getc (stdin); 
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
		"bv", 
		PUTOPTV_S_FILTER, 
		"strip C/C++ comments from code", 
		"b\tdiscard comments and keep code", 
		"v\tdiscard code and keep comments", 
		(char const * ) (0)
	}; 
	void (* function) (void) = exclude; 
	signed c; 
	while ((c = getoptv (argc, argv, optv)) != - 1) 
	{ 
		switch (c) 
		{ 
		case 'b': 
			function = exclude; 
			break; 
		case 'v': 
			function = include; 
			break; 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 
	if (! argc) 
	{ 
		function (); 
	} 
	while ((argc) && (* argv)) 
	{ 
		if (vfopen (* argv)) 
		{ 
			function (); 
		} 
		argv++ ; 
		argc-- ; 
	} 
	return (0); 
} 

