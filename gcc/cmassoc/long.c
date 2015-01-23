/*====================================================================*
 *
 *   ll.c - convert escaped newlines to long lines;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
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
#include "../files/files.h"
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
#include "../tidy/comment.c"
#include "../tidy/control.c"
#include "../tidy/content.c"
#include "../tidy/context.c"
#include "../tidy/escaped.c"
#include "../tidy/literal.c"
#include "../tidy/span.c"
#include "../tidy/keep.c"
#endif

/*====================================================================*
 *
 *   void func (flag_t flags, FILE * ifp, FILE * ofp);
 *
 *   read from ifp and write to ofp; remove escaped newlines to form
 *   one long line from consecutive continuation lines;
 *
 *--------------------------------------------------------------------*/

signed noescape (signed c)

{
	while (c != EOF)
	{
		if (c == '/')
		{
			c = comment (c);
			continue;
		}
		if (isquote (c))
		{
			c = literal (c);
			continue;
		}
		if (c == '#')
		{
			c = control (c, '\n');
			continue;
		}
		c = span (c, '\\', '\n');
		c = keep (c);
	}
	return (c);
}

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv [])

{
	static char const * optv [] =
	{
		"convert escaped newlines to form long lines;",
		PUTOPTV_S_FILTER,
		"",
		(char const *) (0)
	};
	signed (* function) (signed) = noescape;
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
		if (vfopen (* argv))
		{
			function (getc (stdin));
		}
		argc--;
		argv++;
	}
	exit (0);
}

