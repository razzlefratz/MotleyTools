/*====================================================================*
 *
 *   vr.c - variable record copy;
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
#include <limits.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../files/files.h"
#include "../chrlib/charset.h"
#include "../chrlib/ascii.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#include "../tools/error.c"
#include "../files/vfopen.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#include "../files/match.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define VR_B_FILL 	(1 << 0)
#define VR_B_WRAP 	(1 << 1)
#define VR_B_COUNT  	(1 << 2)

/*====================================================================*
 *
 *   void func (size_t linesize, flag_t flag)
 *
 *   read stdin and write stdout; convert variable length records to
 *   fixed length and vice verse; conversion mode is indicated using
 *   fields set in the flagword.
 *
 *   If the FIXED bit is set, fixed length records are output, padding
 *   short records with blanks; otherwise, variable length records are
 *   output, trailing blanks discarded. In either case, long records
 *   are handled as indicated by the TRUNC bit field. Long records are
 *   those that exceed the specified record length.
 *
 *   If the TRUNC bit is set, long records are truncated to the output
 *   record length; otherwise, they are forced to wrap.
 *
 *   #define VR_B_FIXED 0x0001
 *   #define VR_B_TRUNC 0x0002
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (size_t length, flag_t flags)

{
	int last = 0;
	int next = 0;
	int line = 0;
	signed c;
	while ((c = getc (stdin)) != EOF)
	{
		if (c == '\n')
		{
			if (_anyset (flags, VR_B_FILL))
			{
				while (last++ < length)
				{
					putc (SP, stdout);
				}
			}
			putc ('\n', stdout);
			last = next = 0;
		}
		else if (next < length)
		{
			if (c != SP)
			{
				while (last++ < next)
				{
					putc (SP, stdout);
				}
				putc (c, stdout);
			}
			next++;
		}
		else if (_anyset (flags, VR_B_WRAP))
		{
			while (last++ < length)
			{
				putc (SP, stdout);
			}
			putc ('\n', stdout);
			next = last = 0;
			if (c != SP)
			{
				while (last++ < next)
				{
					putc (SP, stdout);
				}
				putc (c, stdout);
			}
			next++;
			line++;
		}
		else line++;
	}
	if (_anyset (flags, VR_B_COUNT) && (line > 0))
	{
		error (0, 0, "truncated %d records", line);
	}
	return;
}

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv [])

{
	char const * optv [] =
	{
		"r:pwc",
		PUTOPTV_S_FILTER,
		"convert text file to fixed or variable length records",
		"r n\tmaximum record length n ",
		"p\tpad short records ",
		"w\twrap long records ",
		"c\tcount truncated records ",
		(char const *) (0)
	};
	flag_t flags = (flag_t) (0);
	size_t length = TEXTLINE_MAX;
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'r':
			length = uintspec (optarg, 0, SHRT_MAX);
			break;
		case 'p':
			_setbits (flags, VR_B_FILL);
			break;
		case 'w':
			_setbits (flags, VR_B_WRAP);
			break;
		case 'c':
			_setbits (flags, VR_B_COUNT);
			break;
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

