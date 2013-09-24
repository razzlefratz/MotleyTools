/*====================================================================*
 *
 *   pkgopt.c - extract package configuration options from stdin; 
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

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/efreopen.c"
#include "../tools/error.c"
#endif

/*====================================================================*
 *
 *   void func (char const *charset, flag_t flags);
 *
 *   read stdin and write stdout; search for lines starting with two
 *   spaces then two dashes; output the two dashes and trailing text;
 *   prefix output lines with a hash and a tab; suffix lines with a
 *   space and a backslash;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void func (flag_t flags)

{
	signed c;
	while ((c = getc (stdin)) != EOF)
	{
		if (c == ' ')
		{
			if ((c = getc (stdin)) == ' ')
			{
				if ((c = getc (stdin)) == '-')
				{
					if ((c = getc (stdin)) == '-')
					{
						putc ('#', stdout);
						putc ('\t', stdout);
						putc ('-', stdout);
						putc ('-', stdout);
						c = getc (stdin);
						while (isalnum (c) || (c == '-'))
						{
							putc (c, stdout);
							c = getc (stdin);
						}
						if (c == '=')
						{
							putc (c, stdout);
							c = getc (stdin);
							if (c == '\"')
							{
								do 
								{
									putc (c, stdout);
									c = getc (stdin);
								}
								while ((c != EOF) && (c != '\"'));
								putc ('\"', stdout);
								c = getc (stdin);
							}
							else while (! isspace (c))
							{
								putc (c, stdout);
								c = getc (stdin);
							}
						}
						else while (! isspace (c))
						{
							putc (c, stdout);
							c = getc (stdin);
						}
						putc (' ', stdout);
						putc ('\\', stdout);
						putc ('\n', stdout);
					}
				}
			}
		}
		while (nobreak (c))
		{
			c = getc (stdin);
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
		"",
		PUTOPTV_S_FUNNEL,
		"extract package configuration options from stdin",
		(char const *) (0)
	};
	flag_t flags = (flag_t) (0);
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
		func (flags);
	}
	while ((argc) && (* argv))
	{
		if (efreopen (* argv, "rb", stdin))
		{
			func (flags);
		}
		argc--;
		argv++;
	}
	exit (0);
}

