/*====================================================================*
 *
 *   enbrace.c - wrap script symbols in braces;
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
#include "../tidy/escaped.c"
#include "../tidy/keep.c.c"
#endif 

/*====================================================================*
 *
 *   signed wrap (signed c, char const * braces);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

signed wrap (signed c, char const * braces)

{
	while (c == '$')
	{
		c = keep (c);
	}
	if (isalnum (c) || (c == '_'))
	{
		putc (* braces++, stdout);
		while (isalnum (c) || (c == '_'))
		{
			putc (c, stdout);
			c = getc (stdin);

#ifdef PHP

			if (c != '-')
			{
				continue;
			}
			c = getc (stdin);
			if (c != '>')
			{
				ungetc (c, stdin);
				c = '-';
				continue;
			}
			putc ('-', stdout);
			putc ('>', stdout);
			c = getc (stdin);

#endif

		}
		putc (* braces--, stdout);
	}
	else if (c == '{')
	{
		do 
		{
			c = keep (c);
		}
		while ((c != '}') && (c != EOF));
	}
	else if (c == '[')
	{
		do 
		{
			c = keep (c);
		}
		while ((c != ']') && (c != EOF));
	}
	else if (c == '(')
	{
		do 
		{
			c = keep (c);
		}
		while ((c != ')') && (c != EOF));
	}
	else if (ispunct (c))
	{
		putc (* braces++, stdout);
		putc (c, stdout);
		c = getc (stdin);
		putc (* braces--, stdout);
		return (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   void function (signed c, char const * braces);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (signed c, char const * braces)

{
	while (c != EOF)
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
			signed o = c;
			c = keep (c);
			while ((c != o) && (c != EOF))
			{
				if (c == '$')
				{
					c = wrap (c, braces);
					continue;
				}
				if (c == '\\')
				{
					c = keep (c);
				}
				c = keep (c);
			}
			c = keep (c);
			continue;
		}
		if (c == '$')
		{
			c = wrap (c, braces);
			continue;
		}
		c = keep (c);
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
		"",
		PUTOPTV_S_FILTER,
		"wrap symbols in braces",
		(char *) (0)
	};
	char const * braces = "{}";
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		function (getc (stdin), braces);
	}
	while ((argc) && (* argv))
	{
		if (vfopen (* argv))
		{
			function (getc (stdin), braces);
		}
		argc--;
		argv++;
	}
	exit (0);
}

