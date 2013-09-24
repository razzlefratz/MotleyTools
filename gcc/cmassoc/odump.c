/*====================================================================*
 *
 *   odump.c - object driven dump utility;
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
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/getoptv.h"
#include "../tools/putoptv.h"
#include "../tools/version.h"
#include "../tools/memory.h"
#include "../tools/number.h"
#include "../tools/error.h"
#include "../tools/chars.h"
#include "../tools/flags.h"
#include "../tools/sizes.h"
#include "../files/files.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/hexview.c"
#include "../tools/hexoffset.c"
#include "../tools/error.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define ODD_VERBOSE  (1 << 0)
#define ODD_SILENCE  (1 << 1)

/*====================================================================*
 *   
 *   void function (file const * file, off_t extent, flag_t flags);
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (file const * file, off_t extent, flag_t flags)

{
	unsigned object = 0;
	unsigned lineno = 0;
	unsigned offset = 0;
	unsigned length = 0;
	char memory [_ADDRSIZE +  1];
	char symbol [_NAMESIZE];
	char string [_LINESIZE];
	char * sp;
	signed c;
	while ((c = getc (stdin)) != EOF)
	{
		if ((c == '#') || (c == ';'))
		{
			do 
			{
				c = getc (stdin);
			}
			while (nobreak (c));
			lineno++;
			continue;
		}
		if (isspace (c))
		{
			if (c == '\n')
			{
				lineno++;
			}
			continue;
		}
		length = 0;
		while (isdigit (c))
		{
			length *= 10;
			length += c - '0';
			c = getc (stdin);
		}
		while (isblank (c))
		{
			c = getc (stdin);
		}
		sp = symbol;
		if (isalpha (c) || (c == '_'))
		{
			do 
			{
				* sp++ = (char)(c);
				c = getc (stdin);
			}
			while (isident (c));
		}
		while (isblank (c))
		{
			c = getc (stdin);
		}
		if (c == '[')
		{
			* sp++ = (char)(c);
			c = getc (stdin);
			while (isblank (c))
			{
				c = getc (stdin);
			}
			while (isdigit (c))
			{
				* sp++ = (char)(c);
				c = getc (stdin);
			}
			while (isblank (c))
			{
				c = getc (stdin);
			}
			* sp = (char)(0);
			if (c != ']')
			{
				error (1, EINVAL, "Have '%s' without ']' on line %d", symbol, lineno);
			}
			* sp++ = (char)(c);
			c = getc (stdin);
		}
		* sp = (char)(0);
		while (isblank (c))
		{
			c = getc (stdin);
		}
		sp = string;
		while (nobreak (c))
		{
			* sp++ = (char)(c);
			c = getc (stdin);
		}
		* sp = (char)(0);
		if (length)
		{
			byte buffer [length];
			if (read (file->file, buffer, length) == (signed)(length))
			{
				if (! object++)
				{
					for (c = 0; c < _ADDRSIZE +  65; c++)
					{
						putc ('-', stdout);
					}
					putc ('\n', stdout);
				}
				printf ("%s %u %s\n", hexoffset (memory, sizeof (memory), offset), length, symbol);
				hexview (buffer, offset, length, stdout);
				for (c = 0; c < _ADDRSIZE +  65; c++)
				{
					putc ('-', stdout);
				}
				putc ('\n', stdout);
			}
		}
		offset += length;
		lineno++;
	}
	if (_allclr (flags, ODD_SILENCE))
	{
		if (offset != (unsigned)(extent))
		{
			error (0, 0, "%s has %u bytes, not " OFF_T_SPEC " bytes.", file->name, offset, extent);
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
		"f:qv",
		"file [file] [...]",
		"object driven dump",
		"f f\tobject definition file",
		"q\tquiet mode",
		"v\tverbose mode",
		(char const *)(0)
	};
	file file = 
	{
		STDIN_FILENO,
		"stdin"
	};
	flag_t flags = (flag_t)(0);
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'f':
			if (! freopen (optarg, "rb", stdin))
			{
				error (1, errno, "%s", optarg);
			}
			break;
		case 'q':
			_setbits (flags, ODD_SILENCE);
			break;
		case 'v':
			_setbits (flags, ODD_VERBOSE);
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (argc > 1)
	{
		error (1, ENOTSUP, ERROR_TOOMANY);
	}
	if ((argc) && (* argv))
	{
		struct stat statinfo;
		stat (* argv, & statinfo);
		if ((file.file = open (file.name = * argv, O_BINARY | O_RDONLY)) == - 1)
		{
			error (0, errno, "%s", file.name);
		}
		else 
		{
			function (& file, statinfo.st_size, flags);
			close (file.file);
		}
		argc--;
		argv++;
	}
	return (0);
}

