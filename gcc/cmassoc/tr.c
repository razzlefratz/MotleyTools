/*====================================================================*
 *
 *   tr.c - character set translation utility;
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
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/*====================================================================*
 *   custom header files; 
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../chrlib/chrlib.h"

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
#include "../chrlib/chrset.c"
#include "../chrlib/chrsub.c"
#include "../chrlib/chruesc.c"
#include "../chrlib/charset.c"
#endif

/*====================================================================*
 *
 *   void function (char const ctable[], flag_t flags);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (char const ctable [], flag_t flags)

{
	signed c;
	while ((c = getc (stdin)) != EOF)
	{
		if (ctable [(unsigned) (c)])
		{
			putc (ctable [(unsigned) (c)], stdout);
		}
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

int main (int argc, char const * argv [])

{
	static char const * optv [] = 
	{
		"f:t:",
		PUTOPTV_S_FILTER,
		"translate characters",
		"f s\tfrom charset is (s) [\"\"]",
		"t s\tto charset is (s) [\"\"]",
		NULL
	};
	char ctable [UCHAR_MAX +  1];
	char control [UCHAR_MAX +  1] = "";
	char replace [UCHAR_MAX +  1] = "";
	flag_t flags = (flag_t) (0);
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'f':
			charset (optarg, 0, control, sizeof (control));
			break;
		case 't':
			charset (optarg, 0, replace, sizeof (replace));
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	chrset (ctable);
	chrsub (ctable, control, replace);
	if (! argc)
	{
		function (ctable, flags);
	}
	while ((argc) && (* argv))
	{
		if (vfopen (* argv))
		{
			function (ctable, flags);
		}
		argc--;
		argv++;
	}
	exit (0);
}

