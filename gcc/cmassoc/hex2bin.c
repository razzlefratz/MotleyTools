/*====================================================================*
 *
 *   hex2bin.c - convert hex files to one binary file;
 *
 *   copy one or more files to stdout; if no files are specified
 *   then copy stdin to stdout;
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
#include <ctype.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/error.c"
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define HEX2BIN_PRIOR 0
#define HEX2BIN_AFTER 0
#define DMP2BIN_PRIOR 10
#define DMP2BIN_AFTER 56

/*====================================================================*
 *
 *   void function (char const * source, size_t prior, size_t after);
 *
 *   discard text prior to column prior and after column after on
 *   each line of a text file; convert remaining text to binary;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (char const * source, size_t prior, size_t after)

{
	unsigned char byte;
	unsigned column = 0;
	unsigned line = 1;
	unsigned digit = 0;
	unsigned value = 0;
	for (column++; read (STDIN_FILENO, & byte, sizeof (byte)) > 0; column++)
	{
		if (isspace (byte))
		{
			if (byte == '\n')
			{
				column = 0;
				line++;
			}
			continue;
		}
		if ((prior < after) && ((column < prior) || (column > after)))
		{
			continue;
		}
		if ((prior > after) && ((column < prior) && (column > after)))
		{
			continue;
		}
		if ((byte >= '0') && (byte <= '9'))
		{
			value *= 16;
			value += byte - '0';
			if (digit++ & 1)
			{
				write (STDOUT_FILENO, & value, sizeof (char));
				value = 0;
			}
			continue;
		}
		if ((byte >= 'A') && (byte <= 'F'))
		{
			value *= 16;
			value += 10;
			value += byte - 'A';
			if (digit++ & 1)
			{
				write (STDOUT_FILENO, & value, sizeof (char));
				value = 0;
			}
			continue;
		}
		if ((byte >= 'a') && (byte <= 'f'))
		{
			value *= 16;
			value += 10;
			value += byte - 'a';
			if (digit++ & 1)
			{
				write (STDOUT_FILENO, & value, sizeof (char));
				value = 0;
			}
			continue;
		}
		error (1, ENOTSUP, "Unexpected character '%c' (0x%02X) on line %d column %d of %s", byte, byte, line, column, source);
	}
	if (digit & 1)
	{
		error (1, ENOTSUP, "File %s has odd digit count (%d)", source, digit);
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
		"convert hex files to single binary file",
		PUTOPTV_S_FUNNEL,
		"a:b:d",
		"a n\tafter column (n) [" LITERAL (HEX2BIN_PRIOR) "]",
		"b n\tbefore column (n) [" LITERAL (HEX2BIN_AFTER) "]",
		"d\tconvert hex dump file (-b" LITERAL (DMP2BIN_PRIOR) " -a" LITERAL (DMP2BIN_AFTER) ")",
		(char const *) (0)
	};
	size_t prior = HEX2BIN_PRIOR;
	size_t after = HEX2BIN_AFTER;
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'a':
			after = (size_t) (uintspec (optarg, 0, 512));
			break;
		case 'b':
			prior = (size_t) (uintspec (optarg, 0, 512));
			break;
		case 'd':
			prior = DMP2BIN_PRIOR;
			after = DMP2BIN_AFTER;
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		function ("stdin", prior, after);
	}
	while ((argc) && (* argv))
	{
		if (! freopen (* argv, "rb", stdin))
		{
			error (1, errno, "%s", * argv);
		}
		function (* argv, prior, after);
		argc--;
		argv++;
	}
	return (0);
}

