/*====================================================================*
 *
 *   enbrace.c - enclose script symbols in braces;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
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

/*====================================================================*
 *
 *   void function (char character, flag_t flags);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void function (char const *braces, flag_t flags) 

{
	signed c = getc (stdin);
	while (c != EOF) 
	{
		if (c == '#') 
		{
			do 
			{
				putc (c, stdout);
				c = getc (stdin);
			}
			while (nobreak (c));
			continue;
		}
		if (c == '$') 
		{
			putc (c, stdout);
			c = getc (stdin);
			if (isalnum (c)) 
			{
				putc (*braces++, stdout);
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
				putc (*braces--, stdout);
				continue;
			}
			if (isdigit (c)) 
			{
				putc (*braces++, stdout);
				putc (c, stdout);
				putc (*braces--, stdout);
				continue;
			}
			if ((c == '#') || (c == '?') || (c == '$')) 
			{
				putc (*braces++, stdout);
				putc (c, stdout);
				putc (*braces--, stdout);
				c = getc (stdin);
				continue;
			}
		}
		putc (c, stdout);
		c = getc (stdin);
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
		"enclose symbols in braces",
		(char *) (0)
	};
	flag_t flags = (flag_t) (0);
	char const * braces = "{}";
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
		function (braces, flags);
	}
	while ((argc) && (* argv)) 
	{
		if (vfopen (* argv)) 
		{
			function (braces, flags);
		}
		argc--;
		argv++;
	}
	exit (0);
}

