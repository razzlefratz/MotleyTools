/*====================================================================*
 *
 *   copyright.c - copyright replacement; 
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
#include <stdlib.h>

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
#include "../tools/emalloc.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../files/vfopen.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#include "../files/makepath.c"
#endif

#ifndef MAKEFILE
#include "../tidy/keep.c"
#include "../tidy/peek.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define NP_VERBOSE (1 << 0)
#define NP_SILENCE (1 << 1)

/*====================================================================*
 *
 *   signed preamble (void * memory, size_t extent, FILE * fp);
 *
 *   read first comment block into memory;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static signed preamble (void * memory, size_t extent, FILE * fp)

{
	signed c = getc (fp);
	memset (memory, 0, extent);
	while (isspace (c))
	{
		c = getc (fp);
	}
	if (c == '/')
	{
		char * sp = (char *) (memory);
		* sp++ = c; c = getc (fp);
		while ((c != '/') && (c != EOF))
		{
			while ((c != '*') && (c != EOF))
			{
				* sp++ = c; c = getc (fp);
			}
			if (c != EOF)
			{
				* sp++ = c; c = getc (fp);
			}
		}
		if (c != EOF)
		{
			* sp++ = c; c = getc (fp);
		}
	}
	return (c);
}

/*====================================================================*
 *
 *   void function (char const * old, char const * new);
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (char * current, char const * old, char const * new, size_t length)

{
	signed c = preamble (current, length, stdin);
	if (strncmp (current, old, length))
	{
		fputs (current, stdout);
	}
	else
	{
		fputs (new, stdout);
	}
	while (c != EOF)
	{
		putc (c, stdout);
		c = getc (stdin);
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
		"o:n:",
		PUTOPTV_S_FILTER,
		"replace module preamble",
		"o s\told preamble file",
		"n s\tnew preamble file",
		(char const *) (0)
	};
	FILE * fp;
	size_t length = STRINGSIZE;
	char * current = (char *) (0);
	char * old = (char *) (0);
	char * new = (char *) (0);
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'o':
			if ((fp = fopen (optarg, "rb")))
			{
				old = emalloc (STRINGSIZE);
				preamble (old, STRINGSIZE, fp);
				fclose (fp);
			}
			break;
		case 'n':
			if ((fp = fopen (optarg, "rb")))
			{
				new = emalloc (STRINGSIZE);
				preamble (new, STRINGSIZE, fp);
				fclose (fp);
			}
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! old || ! * old)
	{
		error (1, ECANCELED, "old preamble is empty");
	}
	if (! new || ! * new)
	{
		error (1, ECANCELED, "new preamble is empty");
	}
	current = emalloc (STRINGSIZE);
	if (! argc)
	{
		function (current, old, new, length);
	}
	while ((argc) && (* argv))
	{
		if (vfopen (* argv))
		{
			function (current, old, new, length);
		}
		argc--;
		argv++;
	}
	exit (0);
}

