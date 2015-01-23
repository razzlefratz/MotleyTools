/*====================================================================*
 *
 *   key.c - random SHA256 key generator;
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
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>

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
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#include "../tools/strincr.c"
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
#define KEY_ADVANCE (1 << 2)

#define MIN 0x20
#define MAX 0x7E

#define SEEDFILE ".keyrc"

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

static unsigned count = 1;

/*====================================================================*
 *
 *   void stop (signo_t signal);
 *
 *   terminate the program; we want to ensure an organized program
 *   exit such that the current pass phrase is saved;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void stop (signo_t signal)

{
	count = 0;
	return;
}

/*====================================================================*
 *
 *   void function (void * secret, size_t length, flag_t flags);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (void * secret, size_t length, flag_t flags)

{
	struct sigaction sa;
	struct sha256 sha256;
	byte digest [SHA256_DIGEST_LENGTH];
	memset (& sa, 0, sizeof (struct sigaction));
	sa.sa_handler = stop;
	sigaction (SIGTERM, & sa, (struct sigaction *) (0));
	sigaction (SIGQUIT, & sa, (struct sigaction *) (0));
	sigaction (SIGTSTP, & sa, (struct sigaction *) (0));
	sigaction (SIGINT, & sa, (struct sigaction *) (0));
	sigaction (SIGHUP, & sa, (struct sigaction *) (0));
	while (count-- > 0)
	{
		memset (digest, 0, sizeof (digest));
		if (_anyset (flags, KEY_ADVANCE) && strincr (secret, length, MIN, MAX))
		{
			error (1, errno, "Can't increment secret");
		}
		SHA256Reset (& sha256);
		SHA256Write (& sha256, secret, length);
		SHA256Fetch (& sha256, digest);
		if (_anyset (flags, KEY_VERBOSE))
		{
			SHA256Print (digest, secret);
		}
		else 
		{
			SHA256Print (digest, (char *) (0));
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
		"random SHA256 key generator",
		"keyfile",
		"f:n:oqv",
		"f s\tuse seedfile (s) [" SEEDFILE "]",
		"n n\tnumber of keys to compute",
		"o\tuse old keyfile value",
		"q\tquiet mode",
		"v\tverbose mode",
		(char const *) (0)
	};
	char const * file = SEEDFILE;
	byte secret [65];
	signed fd;
	flag_t flags = KEY_ADVANCE;
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'f':
			file = optarg;
			break;
		case 'n':
			count = uintspec (optarg, 0, UINT_MAX);
			break;
		case 'o':
			_clrbits (flags, KEY_ADVANCE);
			break;
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
	if (argc)
	{
		error (1, ENOTSUP, ERROR_TOOMANY);
	}
	memset (secret, 0, sizeof (secret));
	if ((fd = open (file, O_BINARY | O_CREAT | O_RDWR, (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH))) == -1)
	{
		error (1, errno, "%s", file);
	}
	if (read (fd, secret, sizeof (secret) -1) == -1)
	{
		error (1, errno, "%s", file);
	}
	for (c = 0; (size_t) (c) < sizeof (secret) -1; c++)
	{
		if (secret [c] < MIN)
		{
			secret [c] = MIN;
		}
		if (secret [c] > MAX)
		{
			secret [c] = MAX;
		}
	}
	function (secret, sizeof (secret) -1, flags);
	if (lseek (fd, 0, SEEK_SET))
	{
		error (1, errno, "%s", file);
	}
	if (write (fd, secret, sizeof (secret) -1) == -1)
	{
		error (1, errno, "%s", file);
	}
	close (fd);
	return (0);
}

