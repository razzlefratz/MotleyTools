/*====================================================================*
 *
 *   fbar.c - extend FORTRAN comment bars;
 *
 *   detect special comment lines and replace them with new ones;
 *   adjust line spacing outside functions and surrounding certain
 *   comment blocks; update information in certain comment blocks;
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
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../files/files.h"
#include "../clang/clang.h"
#include "../linux/linux.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/fgetline.c"
#include "../tools/fputline.c"
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../files/vfopen.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define REMOVE "<<<<<<<"
#define SWITCH "======="
#define INSERT ">>>>>>>"

/*====================================================================*
 *
 *   void func (size_t length, flag_t flags);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (size_t length, flag_t flags)

{
	char buffer [length];
	while (~ (length = fgetline (buffer, sizeof (buffer), stdin)))
	{
		if (! memcmp (buffer, REMOVE, sizeof (REMOVE) - 1))
		{
			continue;
		}
		if (! memcmp (buffer, SWITCH, sizeof (SWITCH) - 1))
		{
			fgetline (buffer, sizeof (buffer), stdin);
			continue;
		}
		if (! memcmp (buffer, INSERT, sizeof (INSERT) - 1))
		{
			continue;
		}
		fputline (buffer, length, stdout);
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
		"",
		PUTOPTV_S_FILTER,
		"remove merge conflicts",
		(char const *) (0)
	};
	flag_t flags = (flag_t) (0);
	size_t length = _LINESIZE;
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
		function (length, flags);
	}
	while ((argc) && (* argv))
	{
		if (vfopen (* argv))
		{
			function (length, flags);
		}
		argc--;
		argv++;
	}
	exit (0);
}

