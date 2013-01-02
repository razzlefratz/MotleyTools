/*====================================================================*
 *
 *   shakey.c - SHA256 key generator;
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
		"qv",
		"phrase [phrase] [...]",
		"SHA256 key generator",
		"q\tquiet mode",
		"v\tverbose mode",
		(char const *) (0)
	};
	struct sha256 sha256;
	byte digest [SHA256_DIGEST_LENGTH];
	char const * phrase;
	char const * sp;
	flag_t flags = (flag_t)(0);
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
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
	if (!argc) 
	{
		putoptv (optv);
		return (0);
	}
	while ((argc) && (* argv)) 
	{
		sp = phrase = * argv;
		while (isprint (*sp)) 
		{
			sp++;
		}
		if (*sp) 
		{
			error (1, ENOTSUP, "Illegal characters: %s", phrase);
		}
		SHA256Reset (&sha256);
		SHA256Write (&sha256, phrase, sp - phrase);
		SHA256Fetch (&sha256, digest);
		if (_allclr (flags, KEY_VERBOSE)) 
		{
			phrase = (char const *)(0);
		}
		SHA256Print (digest, phrase);
		argc--;
		argv++;
	}
	return (0);
}

