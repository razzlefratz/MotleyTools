/*====================================================================*
 *
 *   preamble - replace one preamble with another;
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
		char * bp = (char *) (memory) +  extent;
		char * sp = (char *) (memory);
		if (sp >= bp)
		{
			error (1, EOVERFLOW, "preamble over %d bytes", extent);
		}
		* sp++ = c;
		c = getc (fp);
		while ((c != '/') && (c != EOF))
		{
			while ((c != '*') && (c != EOF))
			{
				if (sp >= bp)
				{
					error (1, EOVERFLOW, "preamble over %d bytes", extent);
				}
				* sp++ = c;
				c = getc (fp);
			}
			if (c != EOF)
			{
				if (sp >= bp)
				{
					error (1, EOVERFLOW, "preamble over %d bytes", extent);
				}
				* sp++ = c;
				c = getc (fp);
			}
		}
		if (c != EOF)
		{
			if (sp >= bp)
			{
				error (1, EOVERFLOW, "preamble over %d bytes", extent);
			}
			* sp++ = c;
			c = getc (fp);
		}
	}
	return (c);
}

/*====================================================================*
 *
 *   void function (char const * remove, char const * insert, char buffer [], size_t length);
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static signed function (char const * remove, char const * insert, char buffer [], size_t length)

{
	signed status;
	signed c = preamble (buffer, length, stdin);
	if (strncmp (remove, buffer, length))
	{
		fputs (buffer, stdout);
		status = 0;
	}
	else 
	{
		fputs (insert, stdout);
		status = 1;
	}
	while (c != EOF)
	{
		putc (c, stdout);
		c = getc (stdin);
	}
	return (status);
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
		"replace one preamble with another",
		"o s\told preamble file",
		"n s\tnew preamble file",
		(char const *) (0)
	};
	FILE * fp;
	size_t length = LINESIZE_MAX;
	char * buffer = "";
	char * remove = "";
	char * insert = "";
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'o':
			if ((fp = fopen (optarg, "rb")))
			{
				remove = emalloc (length);
				preamble (remove, length, fp);
				fclose (fp);
			}
			break;
		case 'n':
			if ((fp = fopen (optarg, "rb")))
			{
				insert = emalloc (length);
				preamble (insert, length, fp);
				fclose (fp);
			}
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! * remove)
	{
		error (1, ECANCELED, "old preamble is empty");
	}
	if (! * insert)
	{
		error (1, ECANCELED, "new preamble is empty");
	}
	buffer = emalloc (length);
	if (! argc)
	{
		function (remove, insert, buffer, length);
	}
	while ((argc) && (* argv))
	{
		if (vfopen (* argv))
		{
			if (function (remove, insert, buffer, length))
			{
				error (0, 0, "%s", * argv);
			}
		}
		argc--;
		argv++;
	}
	exit (0);
}

