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

/*====================================================================*
 *   custom source filed;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/error.c"
#include "../tools/efreopen.c"
#endif

#ifndef MAKEFILE
#include "../files/vfopen.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#endif

/*====================================================================*
 *
 *   void function (signed c)
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (signed c)

{
	while (c != EOF)
	{
		if (isupper (c) || (c == '_'))
		{
			char symbol [1024];
			char * sp = symbol;
			while (isupper (c) || (c == '_'))
			{
				if (sp < (symbol +  sizeof (symbol) - 1))
				{
					* sp++ = c;
				}
				c = getc (stdin);
			}
			* sp = (char) (0);
			if ((sp - symbol) > 2)
			{
				printf ("\t@echo %s=${%s}\n", symbol, symbol);
			}
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
	char const * optv [] = 
	{
		"",
		PUTOPTV_S_FILTER,
		"symbol outpt utility",
		(char const *) (0)
	};
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
		function (getc (stdin));
	}
	while ((argc) && (* argv))
	{
		if (efreopen (* argv, "rb", stdin))
		{
			function (getc (stdin));
		}
		argc--;
		argv++;
	}
	exit (0);
}

