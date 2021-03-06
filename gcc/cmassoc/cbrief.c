/*====================================================================*
 *
 *   cbrief.c - remove C Language comments;
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
#include "../tidy/tidy.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#endif

#ifndef MAKEFILE
#include "../files/vfopen.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#endif

#ifndef MAKEFILE
#include "../tidy/comment.c"
#include "../tidy/literal.c"
#include "../tidy/escaped.c"
#include "../tidy/keep.c"
#include "../tidy/nocomment.c"
#include "../tidy/noliteral.c"
#include "../tidy/noescaped.c"
#include "../tidy/nokeep.c"
#endif

/*====================================================================*
 *
 *   void exclude (void);
 *
 *   read stdin and write stdout; intercept and exclude C Language
 *   style comments that start with double slash or appear between
 *   inverted slash/asterisk character pairs;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void exclude (void)

{
	signed c = getc (stdin);
	while (c != EOF)
	{
		if (c == '/')
		{
			c = nocomment (c);
			continue;
		}
		if (isquote (c))
		{
			c = literal (c);
			continue;
		}
		c = keep (c);
	}
	return;
}

/*====================================================================*
 *
 *   void include (void);
 *
 *   read stdin and write stdout; intercept and include C Language
 *   style comments that start with double slash or appear between
 *   inverted slash/asterisk character pairs;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void include (void)

{
	signed c = getc (stdin);
	while (c != EOF)
	{
		if (c == '/')
		{
			c = comment (c);
			continue;
		}
		if (isquote (c))
		{
			c = noliteral (c);
			continue;
		}
		c = nokeep (c);
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
	static char const * optv [] =
	{
		"strip C/C++ comments from code",
		PUTOPTV_S_FILTER,
		"bv",
		"b\tdiscard comments and keep code",
		"v\tdiscard code and keep comments",
		(char const *) (0)
	};
	void (* function) (void) = exclude;
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'b':
			function = exclude;
			break;
		case 'v':
			function = include;
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		function ();
	}
	while ((argc) && (* argv))
	{
		if (vfopen (* argv))
		{
			function ();
		}
		argv++;
		argc--;
	}
	return (0);
}

