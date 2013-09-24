/*====================================================================*
 *
 *   munge.c - mangle filenames to satisfy your pervrse wishes;
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
#include <ctype.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../files/files.h"

/*====================================================================*
 *   custom source filed;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#endif

#ifndef MAKEFILE
#include "../files/match.c"
#include "../files/vfopen.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define MUNGE_B_EVENT  (1 << 0)
#define MUNGE_B_ERROR  (1 << 1)
#define MUNGE_B_UPPER  (1 << 2)
#define MUNGE_B_LOWER  (1 << 3)

#define MUNGE_S_PREFIX ""
#define MUNGE_S_EXCHANGE " _"
#define MUNGE_S_DISCARD ""

/*====================================================================*
 *   
 *   static void function (char const * pathname, char const * prefix, char const * discard, char const * replace, flag_t flags);
 *   
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (char const * pathname, char const * prefix, char const * discard, char const * replace, flag_t flags)

{
	char filename [FILENAME_MAX];
	char * sp = strcpy (filename, pathname);
	char * cp = sp;
	while (* cp)
	{
		if (* cp++ == PATH_C_EXTENDER)
		{
			sp = cp;
		}
	}
	for (cp = sp; * prefix == * cp; prefix++, cp++);
	if (* prefix)
	{
		cp = sp;
	}
	while (* cp)
	{
		if (strchr (discard, * cp))
		{
			cp++;
			continue;
		}
		if (strchr (replace, * cp))
		{
			* sp++ = * cp++ = * replace;
			continue;
		}
		if (_anyset (flags, MUNGE_B_LOWER))
		{
			* cp = tolower (* cp);
			* sp++ = * cp++;
			continue;
		}
		if (_anyset (flags, MUNGE_B_UPPER))
		{
			* cp = toupper (* cp);
			* sp++ = * cp++;
			continue;
		}
		* sp++ = * cp++;
	}
	if (sp > filename)
	{
		* sp = (char)(0);
	}
	if (strcmp (pathname, filename))
	{
		if (rename (pathname, filename))
		{
			error (1, errno, "%s", pathname);
		}
		if (_anyset (flags, MUNGE_B_EVENT))
		{
			error (0, 0, "%s <-- %s", filename, pathname);
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
	char const * optv [] = 
	{
		"d:lp:uvx:",
		PUTOPTV_S_FILTER,
		"mangle filenames to satisfy your perverse wishes",
		"d s\tdiscard characters in (s) [" LITERAL (MUNGE_S_DISCARD) "]",
		"l\tconvert letters to lower case ",
		"p s\tdiscard prefix (s) [" LITERAL (MUNGE_S_PREFIX) "]",
		"u\tconvert letters to upper case ",
		"v\tverbose mode",
		"x s\texchange characters in (s) [" LITERAL (MUNGE_S_EXCHANGE) "]",
		NULL
	};
	flag_t flags = (flag_t) (0);
	char const * prefix = MUNGE_S_PREFIX;
	char const * discard = MUNGE_S_DISCARD;
	char const * replace = MUNGE_S_EXCHANGE;
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'p':
			prefix = optarg;
			break;
		case 'd':
			discard = optarg;
			break;
		case 'x':
			replace = optarg;
			break;
		case 'u':
			_setbits (flags, MUNGE_B_UPPER);
			_clrbits (flags, MUNGE_B_LOWER);
			break;
		case 'l':
			_setbits (flags, MUNGE_B_LOWER);
			_clrbits (flags, MUNGE_B_UPPER);
			break;
		case 'v':
			_setbits (flags, MUNGE_B_EVENT);
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	while ((argc) && (* argv))
	{
		function (* argv, prefix, discard, replace, flags);
		argc--;
		argv++;
	}
	exit (0);
}

