/*====================================================================*
 *
 *   shakeys.c - SHA256 key generator;
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
#include <unistd.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../crypt/SHA256.h"

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
#include "../crypt/SHA256Reset.c"
#include "../crypt/SHA256Write.c"
#include "../crypt/SHA256Block.c"
#include "../crypt/SHA256Fetch.c"
#include "../crypt/SHA256Print.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define KEY_VERBOSE (1 << 0)
#define KEY_SILENCE (1 << 1)

#define PHRASE_MIN 12
#define PHRASE_MAX 64

/*====================================================================*
 *
 *   void function (flag_t flags);
 *
 *   read phrases from stdin, compute their digest and print both
 *   on stdout; ignore illegal pass phrases;
 *
 *   a pass phrase consists of consecutive ASCII characters in the
 *   range 0x20 through 0x7F; other characters delimit the phrase;
 *   phrases less than HPAVKEY_PHRASE_MIN characters or more than
 *   HPAVKEY_PHRASE_MAX characters are also illegal;
 *
 *   effectively, each text line is a candidate phrase where spaces
 *   are legal and significant; tabs characters are illegal and act
 *   as line breaks;
 *
 *   detected errors are reported along with the input line number;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (flag_t flags)

{
	struct sha256 sha256;
	byte digest [SHA256_DIGEST_LENGTH];
	char phrase [BUFSIZ];
	char * sp;
	unsigned line = 0;
	signed c;
	while ((c = getc (stdin)) != EOF)
	{
		if (! isprint (c))
		{
			if (c == '\n')
			{
				line++;
			}
			continue;
		}
		sp = phrase;
		while (isprint (c))
		{
			if ((size_t) (sp - phrase) < (sizeof (phrase) -1))
			{
				* sp++ = (char) (c);
			}
			c = getc (stdin);
		}
		* sp = (char) (0);
		if ((c != '\r') && (c != '\n') && (c != EOF))
		{
			error (0, ENOTSUP, "illegal characters on line %d", line);
			continue;
		}
		if ((sp - phrase) < PHRASE_MIN)
		{
			error (0, ENOTSUP, "less than %d characters on line %d", PHRASE_MIN, line);
			continue;
		}
		if ((sp - phrase) > PHRASE_MAX)
		{
			error (0, ENOTSUP, "more than %d characters on line %d", PHRASE_MAX, line);
			continue;
		}
		SHA256Reset (& sha256);
		SHA256Write (& sha256, phrase, sp - phrase);
		SHA256Fetch (& sha256, digest);
		if (_allclr (flags, KEY_VERBOSE))
		{
			SHA256Print (digest, (char const *) (0));
			continue;
		}
		SHA256Print (digest, phrase);
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
		"SHA256 key generator",
		"password [password] [...]",
		"qv",
		"q\tquiet mode",
		"v\tverbose mode",
		(char const *) (0)
	};
	flag_t flags = (flag_t) (0);
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'q':
			_setbits (flags, KEY_SILENCE);
			break;
		case 'v':
			_setbits (flags, KEY_VERBOSE);
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		function (flags);
	}
	while ((argc) && (* argv))
	{
		if (! freopen (* argv, "rb", stdin))
		{
			error (0, errno, FILE_CANTOPEN, * argv);
		}
		else 
		{
			function (flags);
		}
		argc--;
		argv++;
	}
	return (0);
}

