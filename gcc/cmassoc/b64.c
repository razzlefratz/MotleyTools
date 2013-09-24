/*====================================================================*
 *
 *   base64.c - base64 encode/decode one or more files;
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
#include <ctype.h>
#include <string.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/base64.h"
#include "../tools/cmassoc.h"
#include "../tools/error.h"

/*====================================================================*
 *   custom source filed;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/error.c"
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
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

#define B64_VERBOSE (1 << 0)
#define B64_SILENCE (1 << 1)
#define B64_ENCODE (1 << 2)
#define B64_DECODE (1 << 3)
#define B64_REPAIR (1 << 4)

/*====================================================================*
 *
 *   void encode (flag_t flags, size_t width);
 *
 *   base64 encode a binary file;
 *
 *   read stdin and write stdout; read up to three bytes at a time 
 *   and write four characters; pad output with '=' to make output 
 *   an even multiple of four bytes to support decoding; line wrap
 *   at width when width is non-zero;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void encode (size_t width, flag_t flags)

{
	unsigned source = 0;
	unsigned output = 0;
	unsigned encode = 0;
	signed c = 0;
	while (c != EOF)
	{
		uint32_t word = 0;
		unsigned byte = 0;
		unsigned bits = BASE64_WORDSIZE - BASE64_BYTESIZE;
		while ((bits) && ((c = getc (stdin)) != EOF))
		{
			bits -= BASE64_BYTESIZE;
			word |= c << bits;
			source++;
			byte++;
		}
		if (byte)
		{
			bits = BASE64_WORDSIZE - BASE64_BYTESIZE;
			for (byte++; (bits) && (byte); byte--)
			{
				bits -= BASE64_CHARSIZE;
				putc (BASE64_CHARSET [(word >> bits) & BASE64_CHARMASK], stdout);
				encode++;
				output++;
			}
			while (bits)
			{
				bits -= BASE64_CHARSIZE;
				putc ('=', stdout);
				encode++;
				output++;
			}
			if ((width) && ! (encode % width))
			{
				putc ('\n', stdout);
				output++;
			}
		}
	}
	if (_anyset (flags, B64_VERBOSE))
	{
		error (0, 0, "Read %d bytes; Wrote %d characters", source, output);
	}
	return;
}

/*====================================================================*
 *
 *   void decode (flag_t flags)
 *
 *   read stdin and write stdout; read up to four base64 characters 
 *   at once and write up to three bytes; character '=' is padding;
 *   ignore newlines; 
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void decode (flag_t flags)

{
	unsigned source = 0;
	unsigned output = 0;
	signed c = 0;
	while (c != EOF)
	{
		uint32_t word = 0;
		unsigned byte = 0;
		unsigned bits = BASE64_WORDSIZE - BASE64_BYTESIZE;
		while ((bits) && ((c = getc (stdin)) != EOF))
		{
			source++;
			if (c == '\n')
			{
				continue;
			}
			else if (isupper (c))
			{
				c -= 'A';
			}
			else if (islower (c))
			{
				c -= 'a';
				c += 26;
			}
			else if (isdigit (c))
			{
				c -= '0';
				c += 52;
			}
			else if (c == '+')
			{
				c = 62;
			}
			else if (c == '/')
			{
				c = 63;
			}
			else if (c == '=')
			{
				bits -= BASE64_CHARSIZE;
				continue;
			}
			else if (_anyset (flags, B64_REPAIR))
			{
				continue;
			}
			else 
			{
				error (1, ENOTSUP, "Input is not base64 encoded");
			}
			bits -= BASE64_CHARSIZE;
			word |= c << bits;
			byte++;
		}
		if (byte--)
		{
			bits = BASE64_WORDSIZE - BASE64_BYTESIZE;
			while ((bits) && (byte))
			{
				bits -= BASE64_BYTESIZE;
				putc ((word >> bits) & BASE64_BYTEMASK, stdout);
				output++;
				byte--;
			}
		}
	}
	if (_anyset (flags, B64_VERBOSE))
	{
		error (0, 0, "Read %d characters; Wrote %d bytes", source, output);
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
	char const * optv [] = 
	{
		"deqrw:v",
		PUTOPTV_S_FILTER,
		"base64 encoder/decoder",
		"d\tdecode input",
		"e\tencode input",
		"q\tquiet mode",
		"r\tremove illegal base64 input characters",
		"w n\twrap base64 output after n columns",
		"v\tverbose mode",
		(char const *) (0)
	};
	flag_t flags = (flag_t) (0);
	size_t width = 0;
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'd':
			_setbits (flags, B64_DECODE);
			break;
		case 'e':
			_setbits (flags, B64_ENCODE);
			break;
		case 'q':
			_setbits (flags, B64_SILENCE);
			break;
		case 'r':
			_setbits (flags, B64_REPAIR);
			break;
		case 'v':
			_setbits (flags, B64_VERBOSE);
			break;
		case 'w':
			width = (signed) (uintspec (optarg, 0, 1024));
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		if (_anyset (flags, B64_DECODE))
		{
			decode (flags);
		}
		else 
		{
			encode (width, flags);
		}
	}
	while ((argc) && (* argv))
	{
		if (vfopen (* argv))
		{
			if (_anyset (flags, B64_DECODE))
			{
				decode (flags);
			}
			else 
			{
				encode (width, flags);
			}
		}
		argc--;
		argv++;
	}
	return (0);
}

