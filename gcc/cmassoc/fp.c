/*====================================================================*
 *
 *   fp.c - file fingerprint;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *   Contributor(s):
 * Charles Maier <cmaier@cmassoc.net>
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <unistd.h>
#include <memory.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../crypt/crypt.h"
#include "../crypt/SHA256.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#include "../tools/efreopen.c"
#include "../tools/hexout.c"
#endif

#ifndef MAKEFILE
#include "../crypt/SHA256Reset.c"
#include "../crypt/SHA256Write.c"
#include "../crypt/SHA256Block.c"
#include "../crypt/SHA256Fetch.c"
#include "../crypt/SHA256Ident.c"
#endif

#ifndef MAKEFILE
#include "../files/filepart.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define FP_B_VERBOSE (1 << 0)
#define FP_B_SILENCE (1 << 1)
#define FP_B_NEWLINE (1 << 2)

/*====================================================================*
 *
 *   int main (int argc, char const * argv [])
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
		PUTOPTV_S_FUNNEL,
		"file finger-printer",
		"q\tsuppress routine messages",
		"v\tprint additions messages",
		(char const *) (0)
	};
	byte buffer [BUFFERSIZE];
	byte digest [DIGESTSIZE];
	flag_t flags = (flag_t) (0);
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'q':
			_setbits (flags, FP_B_SILENCE);
			break;
		case 'v':
			_setbits (flags, FP_B_VERBOSE);
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		SHA256Ident (STDIN_FILENO, buffer, sizeof (buffer), digest);
		hexout (digest, sizeof (digest), '\0', '\0', stdout);
		printf ("\n");
	}
	while ((argc) && (* argv))
	{
		if (efreopen (* argv, "rb", stdin))
		{
			SHA256Ident (STDIN_FILENO, buffer, sizeof (buffer), digest);
			hexout (digest, sizeof (digest), '\0', '\0', stdout);
			if (_anyset (flags, FP_B_VERBOSE))
			{
				printf (" %s", * argv);
			}
			printf ("\n");
		}
		argc--;
		argv++;
	}
	return (0);
}

