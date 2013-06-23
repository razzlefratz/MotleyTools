/*====================================================================*
 *
 *   detag.c - remove markup tags;
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
#include <ctype.h>
#include <stdlib.h>

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
#include "../tools/efreopen.c"
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
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
 *   program functions;
 *--------------------------------------------------------------------*/

static signed markup (signed c);
static signed pcdata (signed c);

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
		"",
		PUTOPTV_S_FUNNEL,
		"remove sgml/html/xhtml/xml markup",
		(char const *)(0)
	};
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		default:
			break;
		}
	}
	argc-= optind;
	argv+= optind;
	if (!argc) 
	{
		pcdata (getc (stdin));
	}
	while ((argc) && (* argv)) 
	{
		if (efreopen (* argv, "rb", stdin)) 
		{
			pcdata (getc (stdin));
		}
		argc--;
		argv++;
	}
	exit (0);
}

