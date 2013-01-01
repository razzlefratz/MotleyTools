/*====================================================================*
 *
 *   sbrief.c - remove comments, minimize space and concatenate 
 *   continuation lines;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
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
#include "../tools/error.c"
#include "../files/vfopen.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#endif

/*====================================================================*
 *
 *   void function (signed comment, signed tab, flag_t flags);
 *
 *   read stdin and write stdout; discard comment lines, concatenate
 *   continuation lines and replace spaces and tabs with one space;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static void function (signed comment, flag_t flags) 

{
	signed c = (char) (0);
	signed o = (char) (0);
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
				}
				while (isblank (c));
				if (nobreak (c)) 
				{
					putc (' ', stdout);
				}
				continue;
			}
			if (c == '\\') 
			{
				c = getc (stdin);
				if (nobreak (c)) 
				{
					putc ('\\', stdout);
					putc (c, stdout);
				}
				c = getc (stdin);
				continue;
			}
			if (isquote (c)) 
			{
				putc (c, stdout);
				o = getc (stdin);
				while ((o != c) && (c != EOF)) 
				{
					if (o == '\\') 
					{
						putc (o, stdout);
						o = getc (stdin);
					}
					putc (o, stdout);
					o = getc (stdin);
				}
				putc (c, stdout);
				c = getc (stdin);
				continue;
			}
			putc (c, stdout);
			c = getc (stdin);
		}
		putc ('\n', stdout);
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
		"c:t:",
		PUTOPTV_S_FILTER,
		"remove comments, concatenate continuation lines and condense space",
		"c c\tcomment character is (c) ['#']",
		(char const *) (0)
	};
	flag_t flags = (flag_t) (0);
	signed comment = '#';
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'c':
			comment = *optarg;
			break;
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (!argc) 
	{
		function (comment, flags);
	}
	while ((argc) && (* argv)) 
	{
		if (vfopen (* argv)) 
		{
			function (comment, flags);
		}
		argc--;
		argv++;
	}
	exit (0);
}

