/*====================================================================*
 *
 *   bang.c - insert shell bang path;
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
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../clang/clang.h"
#include "../linux/linux.h"
#include "../files/files.h"

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
#include "../files/vfopen.c"
#include "../files/makefind.c"
#include "../files/partpath.c"
#include "../files/partfile.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#include "../files/find.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define SHBANG_EXECUTE  (1 << 0)

/*====================================================================*
 *
 *   void function (struct _find_ *find, size_t length, flag_t flags);
 *
 *   write shbang header to stdout; we write find-pathname, instead
 *   of find->fullname, because the main function set that buffer to
 *   the desired path instead of the actual path;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (struct _find_ * find, size_t length, flag_t flags)

{
	time_t now = time (& now);
	struct tm * tm = localtime (& now);
	char buffer [length];
	length = 0;
	length += snprintf (buffer +  length, sizeof (buffer) - length, "#!/bin/bash\n");
	length += snprintf (buffer +  length, sizeof (buffer) - length, "# file: %s\n", find->pathname);
	length += snprintf (buffer +  length, sizeof (buffer) - length, "# Published %04d by Charles Maier Associates Limited for internal use;\n", tm->tm_year +  1900);
	length += snprintf (buffer +  length, sizeof (buffer) - length, "\n");
	write (STDOUT_FILENO, buffer, length);
	while ((length = read (STDIN_FILENO, buffer, sizeof (buffer))) > 0)
	{
		write (STDOUT_FILENO, buffer, length);
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
	extern FIND find;
	static char const * optv [] =
	{
		"e:p:x",
		PUTOPTV_S_FILTER,
		"insert shell bang path header",
		"e s\tpathname defined by environement variable s",
		"p s\tpathname string is s",
		"x\tmake file executable",
		(char const *) (0)
	};
	char const * pathname = "";
	flag_t flags = (flag_t) (0);
	size_t length = _LINESIZE;
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'e':
			if ((pathname = getenv (optarg)) == (char *) (0))
			{
				error (1, errno, "symbol %s not defined", optarg);
			}
			break;
		case 't':
			if ((pathname = getenv ("CMTOOLS")) == (char *) (0))
			{
				error (1, errno, "symbol CMTOOLS is undefined");
			}
			break;
		case 'p':
			pathname = optarg;
			break;
		case 'x':
			_setbits (flags, SHBANG_EXECUTE);
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		function (& find, length, flags);
	}
	while ((argc) && (* argv))
	{
		makefind (& find, * argv);
		if (vfopen (find.fullname))
		{
			if ((! pathname) || (! * pathname))
			{
				strcpy (find.pathname, pathname);
			}
			strcat (find.pathname, PATH_S_EXTENDER);
			strcat (find.pathname, find.filename);
			function (& find, length, flags);
			if (_anyset (flags, SHBANG_EXECUTE))
			{
				if (chmod (find.fullname, 0755))
				{
					error (0, errno, "can't chmod %s", find.fullname);
				}
			}
		}
		argc--;
		argv++;
	}
	exit (0);
}

