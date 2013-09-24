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

#define FBAR_EXECUTE  (1 << 0)

#define FBAR_WIDTH 68
#define FBAR_START '#'
#define FBAR_SPACE ' '

/*====================================================================*
 *
 *   void func (char start, char space, size_t width, size_t length, flag_t flags);
 *
 *   read from stdin and write to stdout; re-write FORTRAN comments
 *   where column one contains the start character; comments having 
 *   a space follwed by CUPPER or CLOWER are always re-written;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (char start, char space, size_t width, size_t length, flag_t flags)

{
	char buffer [length];
	size_t column = 0;
	width++;
	width++;
	if (width > length)
	{
		width = length;
	}
	for (column = 0; ~ (length = fgetline (buffer, sizeof (buffer), stdin)); column = 0)
	{
		if (buffer [column++] != start)
		{
			fputline (buffer, length, stdout);
			continue;
		}
		if (buffer [column++] != space)
		{
			fputline (buffer, length, stdout);
			continue;
		}
		if (buffer [column] == CUPPER)
		{
			while (column < width)
			{
				buffer [column++] = CUPPER;
			}
			fputline (buffer, 0, stdout);
			fputline (buffer, column, stdout);
			continue;
		}
		if (buffer [column] == CLOWER)
		{
			while (column < width)
			{
				buffer [column++] = CLOWER;
			}
			fputline (buffer, column, stdout);
			fputline (buffer, 0, stdout);
			continue;
		}
		fputline (buffer, length, stdout);
	}
	fputline (buffer, column, stdout);
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
		"c:w:x",
		PUTOPTV_S_FILTER,
		"extend FORTRAN style comment bars",
		"c c\tcomments start with character c [" LITERAL (FBAR_START) "]",
		"w n\tbar width is (n) [" LITERAL (FBAR_WIDTH) "]",
		"x\tmake file executable",
		(char const *) (0)
	};
	flag_t flags = (flag_t) (0);
	size_t length = _LINESIZE;
	size_t width = FBAR_WIDTH;
	char start = FBAR_START;
	char space = FBAR_SPACE;
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'c':
			start = (char) (* optarg);
			break;
		case 'x':
			_setbits (flags, FBAR_EXECUTE);
			break;
		case 'w':
			width = uintspec (optarg, 0, length);
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		function (start, space, width, length, flags);
	}
	while ((argc) && (* argv))
	{
		if (vfopen (* argv))
		{
			function (start, space, width, length, flags);
			if (_anyset (flags, FBAR_EXECUTE))
			{
				if (chmod (* argv, 0755))
				{
					error (0, errno, "can't chmod %s", * argv);
				}
			}
		}
		argc--;
		argv++;
	}
	exit (0);
}

