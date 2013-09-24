/*====================================================================*
 *
 *   defix.c - extract prefix and suffix strings;
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
#include <unistd.h>
#include <limits.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../strlib/strlib.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#include "../tools/todigit.c"
#endif

#ifndef MAKEFILE
#include "../strlib/struesc.c"
#endif

#ifndef MAKEFILE
#include "../chrlib/chruesc.c"
#endif

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

int main(int argc, char const * argv[])

{
	static char const * optv[] = 
	{
		"c:f:imops",
		PUTOPTV_S_DIVINE,
		"extract prefix or suffix part of delimited argument",
		"c c\tcomponent separator is c ['.']",
		"f s\tformat string is s [\"%s\"]",
		"i\tbreak on initial separator",
		"m\tseparator is required",
		"o\tseparator is optional",
		"p\textract prefix",
		"s\textract suffix",
		(char const *)(0)
	};
	char const * format = "%s";
	char character = '.';
	bool initial = false;
	bool optional = false;
	bool right = false;
	char * string;
	char * prefix;
	char * suffix;
	signed c;
	while (~ (c = getoptv(argc, argv, optv)))
	{
		switch (c)
		{
		case 'c':
			character = * optarg;
			break;
		case 'f':
			format = struesc((char *)(optarg));
			break;
		case 'i':
			initial = true;
			break;
		case 'm':
			optional = false;
			break;
		case 'o':
			optional = true;
			break;
		case 'p':
			right = false;
			break;
		case 's':
			right = true;
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	while ((argc) && (* argv))
	{
		string = (char *)(* argv);
		for (prefix = suffix = string; * prefix != (char)(0); prefix++)
		{
			if (* prefix == character)
			{
				suffix = prefix;
				if (initial)
				{
					break;
				}
			}
		}
		if (* suffix == character)
		{
			* suffix++ = (char)(0);
			prefix = string;
		}
		else if(optional)
		{
			suffix = prefix;
			prefix = string;
		}
		printf (format, (right)? suffix: prefix);
		printf ("\n");
		argc--;
		argv++;
	}
	exit (0);
}

