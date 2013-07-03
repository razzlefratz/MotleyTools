/*====================================================================*
 *
 *   pkg - extract and print GNU/Linux package name components;
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
#include <unistd.h>
#include <limits.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../strlib/strlib.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/fgetline.c"
#include "../tools/todigit.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../strlib/struesc.c"
#include "../chrlib/chruesc.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define PKG_B_PACKAGE (1 << 0)
#define PKG_B_VERSION (1 << 1)
#define PKG_B_TRAILER (1 << 2)

/*====================================================================*
 *
 *   void function (char string[], char const *extender, flag_t flags);
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (char const string [], char const * extenders [], flag_t flags) 

{
	struct _package_ 
	{
		char archive [FILENAME_MAX];
		char package [FILENAME_MAX];
		char version [FILENAME_MAX];
		char trailer [FILENAME_MAX];
	}
	file = 
	{
		"",
		"",
		""
	};
	char const * package;
	char const * version;
	char const * trailer;
	for (package = version = trailer = string; * string != (char) (0); string++) 
	{
		if (* string == '/') 
		{
			package = string + 1;
			version = string + 1;
			trailer = string + 1;
			continue;
		}
		if (* string == '-') 
		{
			version = string;
			trailer = string;
			continue;
		}
		if (* string == '.') 
		{
			char const ** extender = extenders;
			trailer = string;
			while (* extender != (char const *) (0)) 
			{
				if (!strcmp (string, * extender++)) 
				{
					while (*++string != (char) (0));
					break;
				}
			}
			if (* string == (char)(0)) 
			{
				break;
			}
		}
	}
	if ((package < version) && (version < trailer)) 
	{
		memcpy (file.package, package, version - package);
		file.package [version - package] = (char) (0);
		version++;
		memcpy (file.version, version, trailer - version);
		file.version [trailer - version] = (char) (0);
		trailer++;
		memcpy (file.trailer, trailer, string - trailer);
		file.trailer [string - trailer] = (char) (0);
		memcpy (file.archive, package, string - package);
		file.archive [string - package] = (char) (0);
		switch (flags & (PKG_B_PACKAGE | PKG_B_VERSION | PKG_B_TRAILER)) 
		{
		case PKG_B_PACKAGE | PKG_B_VERSION:
			printf ("%s-%s\n", file.package, file.version);
			break;
		case PKG_B_PACKAGE:
			printf ("%s\n", file.package);
			break;
		case PKG_B_VERSION:
			printf ("%s\n", file.version);
			break;
		case PKG_B_TRAILER:
			printf ("%s\n", file.trailer);
			break;
		default:
			printf ("%s\n", file.archive);
			break;
		}
	}
	return;
}

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"pvex:",
		PUTOPTV_S_DIVINE,
		"isolate and segment package name string",
		"p\tprint package name",
		"v\tprint version number",
		"e\tprint file extension",
		"x s\tremove extender s [.tar.bz2]",
		(char const *) (0)
	};
	char const ** extender;
	char const * extenders [100] = 
	{
		".tar",
		".tgz",
		".tar.bz2",
		".tar.gz",
		".md5",
		".md5sum",
		".asc",
		(char const *) (0)
	};
	flag_t flags = (flag_t) (0);
	signed c;
	for (extender = extenders; * extender != (char const *) (0); extender++);
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'x':
			* extender++ = optarg;
			* extender = (char const *) (0);
			break;
		case 'p':
			_setbits (flags, PKG_B_PACKAGE);
			break;
		case 'v':
			_setbits (flags, PKG_B_VERSION);
			break;
		case 'e':
			_setbits (flags, PKG_B_TRAILER);
			break;
		default:
			break;
		}
	}
	argc-= optind;
	argv+= optind;
	if (!argc) 
	{
		char pathname [TEXTLINE_MAX];
		signed length;
		while ((length = fgetline (pathname, sizeof (pathname), stdin)) != -1) 
		{
			while (isspace (pathname [--length])) 
			{
				pathname [length] = (char) (0);
			}
			function ((char const *) (pathname), extenders, flags);
		}
	}
	while ((argc) && (* argv)) 
	{
		function (* argv, extenders, flags);
		argc--;
		argv++;
	}
	exit (0);
}

