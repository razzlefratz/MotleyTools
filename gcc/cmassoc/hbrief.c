/*====================================================================*
 *
 *   hbrief.c - remove HTLM attributes; 
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
#include "../files/files.h"
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
#include "../tidy/nocomment.c"
#include "../tidy/nocontext.c"
#include "../tidy/nocontent.c"
#include "../tidy/noliteral.c"
#include "../tidy/noescaped.c"
#include "../tidy/keep.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#ifndef nmtoken
#define nmtoken(c) (isalnum(c) || (c == '_') || (c == ':') || (c == '.') || (c == '-'))
#endif

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

unsigned lineno = 0; 

/*====================================================================*
 *   program functions;
 *--------------------------------------------------------------------*/

static signed markup (signed c); 
static signed pcdata (signed c); 

/*====================================================================*
 *
 *   signed nocomment (signed c) 
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static signed _nocomment (signed c) 

{ 
	c = getc (stdin); 
	if (c == '-') 
	{ 
		do 
		{ 
			c = getc (stdin); 
		} 
		while (c == '-'); 
		do 
		{ 
			c = nocontent (c, '-'); 
		} 
		while ((c != '-') && (c != EOF)); 
		do 
		{ 
			c = getc (stdin); 
		} 
		while (c == '-'); 
	} 
	return (c); 
} 

/*====================================================================*
 *
 *   signed markup (signed c) 
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static signed markup (signed c) 

{ 
	c = getc (stdin); 
	if (c == '!') 
	{ 
		c = getc (stdin); 
		if (c == '-') 
		{ 
			c = _nocomment (c); 
		} 
		c = nocontext (c, '>'); 
		return (c); 
	} 
	else if ((c == '?') || (c == '%')) 
	{ 
		do 
		{ 
			c = nocontext (c, c); 
		} 
		while ((c != '>') && (c != EOF)); 
		c = getc (stdin); 
		return (c); 
	} 
	while ((c != '/') && (c != '>') && (c != EOF)) 
	{ 
		if (isspace (c)) 
		{ 
			do 
			{ 
				c = getc (stdin); 
			} 
			while (isspace (c)); 
			continue; 
		} 
		if (nmtoken (c)) 
		{ 
			do 
			{ 
				c = getc (stdin); 
			} 
			while (nmtoken (c)); 
			continue; 
		} 
		if (isquote (c)) 
		{ 
			c = noliteral (c); 
			continue; 
		} 
		c = getc (stdin); 
	} 
	if (c == '>') 
	{ 
		c = getc (stdin); 
		c = pcdata (c); 
		c = getc (stdin); 
	} 
	c = nocontext (c, '>'); 
	return (c); 
} 

/*====================================================================*
 *
 *   signed pcdata (signed c) 
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static signed pcdata (signed c) 

{ 
	while ((c != '/') && (c != EOF)) 
	{ 
		while ((c != '<') && (c != EOF)) 
		{ 
			c = keep (c); 
		} 
		c = markup (c); 
	} 
	return (c); 
} 

/*====================================================================*
 *
 *   int element (signed c) 
 *
 *   remove attributes from markup element, leaving a minimal tag;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static signed element (signed c) 

{ 
	c = getc (stdin); 
	if (c == '%') 
	{ 
		do 
		{ 
			c = nocontext (c, c); 
		} 
		while ((c != '>') && (c != EOF)); 
	} 
	else if ((c == '!') || (c == '?')) 
	{ 
		do 
		{ 
			c = keep (c); 
		} 
		while (isalnum (c) || ((char)(c) == '-')); 
		c = nocontext (c, '>'); 
	} 
	else if (isalpha (c) || ((char)(c) == '/')) 
	{ 
		do 
		{ 
			c = keep (c); 
		} 
		while (isident (c)); 
		c = nocontext (c, '>'); 
	} 
	return (c); 
} 

/*====================================================================*
 *
 *   signed document (signed c) 
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static signed document (signed c) 

{ 
	while (c != EOF) 
	{ 
		if (c == '<') 
		{ 
			putc ('<', stdout); 
			c = element (c); 
			putc ('>', stdout); 
			continue; 
		} 
		c = keep (c); 
	} 
	return (c); 
} 

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{ 
	static char const * optv [] = 
	{ 
		"am", 
		PUTOPTV_S_FILTER, 
		"remove markup from document", 
		"a\tremove attributes from markup", 
		"m\tremove markup from document", 
		(char const *) (0)
	}; 
	signed (* function) (signed) = pcdata; 
	signed c; 
	while (~ (c = getoptv (argc, argv, optv))) 
	{ 
		switch (c) 
		{ 
		case 'a': 
			function = document; 
			break; 
		case 't': 
			function = pcdata; 
			break; 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 
	if (!argc) 
	{ 
		function (getc (stdin)); 
	} 
	while ((argc) && (* argv)) 
	{ 
		if (vfopen (* argv)) 
		{ 
			function (getc (stdin)); 
		} 
		argc--; 
		argv++; 
	} 
	exit (0); 
} 

