/*====================================================================*
 *
 *   ds.c - digital dactyloscope;
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
#include <ctype.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/getoptv.h"
#include "../tools/error.h"
#include "../tools/sizes.h"
#include "../files/files.h"
#include "../crypt/SHA256.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#include "../tools/efreopen.c"
#endif

#ifndef MAKEFILE
#include "../crypt/SHA256Reset.c"
#include "../crypt/SHA256Write.c"
#include "../crypt/SHA256Block.c"
#include "../crypt/SHA256Fetch.c"
#include "../crypt/SHA256Ident.c"
#include "../crypt/SHA256Match.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define REGISTRY "registry.txt"

/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
 *
 *   digital dactyloscope;
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
		"digital dactyloscope",
		"file [file] [...]",
		"f:",
		"f f\tfingerprint registry [" REGISTRY "]",
		(char const *) (0)
	};
	byte buffer [BUFFERSIZE];
	byte digest [DIGESTSIZE];
	char const * registry = REGISTRY;
	signed fd;
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'f':
			registry = optarg;
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if ((fd = open (registry, O_BINARY | O_RDONLY)) == -1)
	{
		error (1, errno, FILE_CANTOPEN, registry);
	}
	while ((argc) && (* argv))
	{
		if (lseek (fd, 0, SEEK_SET))
		{
			error (1, errno, FILE_CANTHOME, registry);
		}
		if (efreopen (* argv, "rb", stdin))
		{
			SHA256Ident (fileno (stdin), buffer, sizeof (buffer), digest);
			printf ("%s %s\n", SHA256Match (fd, digest)? "+": "-", * argv);
		}
		argc--;
		argv++;
	}
	close (fd);
	return (0);
}

