/*====================================================================*
 *
 *   case.c - character case conversion;
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
#include "../strlib/strlib.h"
#include "../chrlib/chrlib.h"
#include "../tidy/tidy.h"

/*====================================================================*
 *   custom source filed;
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
#include "../strlib/strcomp.c"
#include "../strlib/strconv.c"
#endif

#ifndef MAKEFILE
#include "../chrlib/chrlwr.c"
#include "../chrlib/chrupr.c"
#endif

#ifndef MAKEFILE
#include "../tidy/literal.c"
#include "../tidy/escaped.c"
#include "../tidy/keep.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define CASE_B_UPPER  (1 << 0)
#define CASE_B_LOWER  (1 << 1)
#define CASE_B_TITLE  (1 << 2)
#define CASE_B_APOST  (1 << 3)
#define CASE_B_QUOTE  (1 << 4)

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

unsigned lineno = 0;

/*====================================================================*
 *
 *   void function(signed c, flag_t flags)
 *
 *   This function performs lower-to-upper or upper-to-lower case 
 *   character code conversion on a file; literal text enclosed in 
 *   apostrophes or quotes is not converted when certain flagword 
 *   bits are set:
 *
 *      CASE_B_UPPER :== convert to upper case;
 *      CASE_B_LOWER :== convert to lower case;
 *      CASE_B_APOST :== apostrophe encloses a literal
 *      CASE_B_QUOTE :== quote encloses a literal
 *
 *   Flagword bit fields should be globally defined; recommended values
 *   are provided as follows;
 *
 *      #define  CASE_B_UPPER 0x0001
 *      #define  CASE_B_LOWER 0x0002
 *      #define  CASE_B_TITLE CASE_B_UPPER|CASE_B_LOWER
 *      #define  CASE_B_APOST 0x0004
 *      #define  CASE_B_QUOTE 0x0008
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function(signed c, flag_t flags)

{
	while (c != EOF)
	{
		if (isalpha(c))
		{
			if (_anyset(flags, CASE_B_UPPER))
			{
				do 
				{
					c = keep(toupper(c));
				}
				while (isalpha(c));
				continue;
			}
			if (_anyset(flags, CASE_B_LOWER))
			{
				do 
				{
					c = keep(tolower(c));
				}
				while (isalpha(c));
				continue;
			}
			if (_anyset(flags, CASE_B_TITLE))
			{
				c = toupper(c);
			}
			do 
			{
				c = keep(c);
			}
			while (isalnum(c));
			continue;
		}
		if ((c == '\"') && _anyset(flags, CASE_B_QUOTE))
		{
			c = literal(c);
			continue;
		}
		if ((c == '\'') && _anyset(flags, CASE_B_APOST))
		{
			c = literal(c);
			continue;
		}
		c = escaped(c);
	}
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

int main(int argc, char const * argv[])

{
	char const * optv[] = 
	{
		"luxtds",
		PUTOPTV_S_FILTER,
		"converts files to upper or lower case",
		"l\tconvert text to lower case ",
		"u\tconvert text to upper case ",
		"t\tconvert text to title case ",
		"d\texclude double quoted (\") text",
		"s\texclude single quoted (\') text",
		(char const *) (0)
	};
	flag_t flags = (flag_t)(0);
	signed c;
	while (~ (c = getoptv(argc, argv, optv)))
	{
		switch (c)
		{
		case 'u':
			_clrbits (flags, CASE_B_LOWER | CASE_B_TITLE);
			_setbits (flags, CASE_B_UPPER);
			break;
		case 'l':
			_clrbits (flags, CASE_B_UPPER | CASE_B_TITLE);
			_setbits (flags, CASE_B_LOWER);
			break;
		case 't':
			_clrbits (flags, CASE_B_LOWER | CASE_B_UPPER);
			_setbits (flags, CASE_B_TITLE);
			break;
		case 'd':
			_setbits (flags, CASE_B_QUOTE);
			break;
		case 's':
			_setbits (flags, CASE_B_APOST);
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		function (getc(stdin), flags);
	}
	while ((argc) && (* argv))
	{
		if (vfopen(* argv))
		{
			function (getc(stdin), flags);
		}
		argv++;
		argc--;
	}
	exit (0);
}

