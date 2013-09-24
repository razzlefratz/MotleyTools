/*====================================================================*
 *
 *   l2p.c - list-to-pair organizer;
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
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/getoptv.h"
#include "../tools/putoptv.h"
#include "../tools/version.h"
#include "../tools/error.h"
#include "../tools/chars.h"
#include "../tools/sizes.h"
#include "../tools/flags.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/error.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define L2P_VERBOSE  (1 << 0)
#define L2P_SILENCE  (1 << 1)
#define L2P_REVERSE  (1 << 2)

/*====================================================================*
 *   
 *   void function (flag_t flags);
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (flag_t flags)

{
	unsigned lineno = 1;
	char symbol [_NAMESIZE];
	char string [_LINESIZE];
	char * sp;
	signed c;
	while ((c = getc (stdin)) != EOF)
	{
		while (isblank (c))
		{
			c = getc (stdin);
		}
		sp = symbol;
		if (isident (c))
		{
			do 
			{
				* sp++ = c;
				c = getc (stdin);
			}
			while (isident (c) || (c == '-') || (c == '.'));
		}
		* sp = (char) (0);
		while (isblank (c))
		{
			c = getc (stdin);
		}
		if (c == ':')
		{
			do 
			{
				c = getc (stdin);
			}
			while (isblank (c));
			do 
			{
				sp = string;
				if (isident (c))
				{
					do 
					{
						* sp++ = c;
						c = getc (stdin);
					}
					while (isident (c) || (c == '-') || (c == '.'));
				}
				* sp = (char) (0);
				while (isblank (c))
				{
					c = getc (stdin);
				}
				if (_anyset (flags, L2P_REVERSE))
				{
					printf ("%s:%s;\n", string, symbol);
				}
				else 
				{
					printf ("%s:%s;\n", symbol, string);
				}
			}
			while ((c != ';') && (c != '\n') && (c != EOF));
		}
		while ((c != ';') && (c != '\n') && (c != EOF))
		{
			c = getc (stdin);
		}
		lineno++;
	}
	fclose (stdin);
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
		"qvx",
		"file [file] [...]",
		"list-to-pair conversion",
		"q\tquiet mode",
		"v\tverbose mode",
		"x\texchange order",
		(char const *) (0)
	};
	flag_t flags = (flag_t) (0);
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'q':
			_setbits (flags, L2P_SILENCE);
			break;
		case 'v':
			_setbits (flags, L2P_VERBOSE);
			break;
		case 'x':
			_setbits (flags, L2P_REVERSE);
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		function (flags);
	}
	while ((argc) && (* argv))
	{
		if (! freopen (* argv, "rb", stdin))
		{
			error (1, errno, "%s", * argv);
		}
		function (flags);
		argc--;
		argv++;
	}
	return (0);
}

