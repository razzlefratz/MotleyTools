/*====================================================================*
 *
 *   pkg.c - convert pkgconfig files to csv dependency file;
 *
 *   read "*.  Motley Tools by Charles Maier;
 *   and write dependencies to stdout;
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
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../files/files.h"
#include "../strlib/strlib.h"
#include "../chrlib/charset.h"
#include "../scan/scan.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/efreopen.c"
#include "../tools/emalloc.c"
#include "../tools/fgetline.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../files/match.c"
#include "../files/find.c"
#include "../files/partpath.c"
#include "../files/partfile.c"
#endif

#ifndef MAKEFILE
#include "../scan/scaninput.c"
#include "../scan/scanreset.c"
#include "../scan/scanuntil.c"
#include "../scan/scanwhile.c"
#include "../scan/scanbreak.c"
#include "../scan/scantoken.c"
#include "../scan/scanalnum.c"
#include "../scan/scandigit.c"
#include "../scan/scanspace.c"
#include "../scan/scanflush.c"
#include "../scan/havetoken.c"
#include "../scan/havebreak.c"
#include "../scan/nexttoken.c"
#include "../scan/nextbreak.c"
#include "../scan/tokentext.c"
#include "../scan/copytoken.c"
#include "../scan/tokensize.c"
#include "../scan/istoken.c"
#include "../scan/isbreak.c"
#include "../scan/isclass.c"
#endif

#ifndef MAKEFILE
#include "../strlib/strsplit.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define MAX_PATHS 10
#define MAX_FILES 10

/*====================================================================*
 *   program functions;
 *--------------------------------------------------------------------*/

static void findfile (FIND * find, flag_t flags);
static void testfile (FIND * find, flag_t flags);

/*====================================================================*
 *
 *   static void noversion (char package[]);
 *
 *   convert package to lower case and truncate at the rightmost
 *   hyphen; for example, Gnome-VFS-2.3.4 becomes gnome-vfs;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static char * noversion (char package [])

{
	char * version;
	for (version = package; * package != (char) (0); ++ package)
	{
		if (* package == '-')
		{
			version = package;
			continue;
		}
		if (isupper (* package))
		{
			* package = * package +  ('a' - 'A');
			continue;
		}
	}
	if (* version == '-')
	{
		* version = (char) (0);
		version++;
	}
	return (version);
}

/*====================================================================*
 *
 *   static void extract (SCAN *scan, char buffer[], size_t length);
 *
 *   extract package name and discard version part;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void extract (SCAN * scan, char buffer [], size_t length)

{
	scanuntil (scan, gcsSpace ".,;");
	copytoken (scan, buffer, length);
	noversion (buffer);
	return;
}

/*====================================================================*
 *
 *   static void function (FIND * find, flag_t flags);
 *
 *   read a linux package description file and string and write
 *   dependencies to stdout;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (FIND * find, flag_t flags)

{
	if (! match (find->filename, find->wildcard))
	{
		return;
	}
	if (efreopen (find->fullname, "rb", stdin))
	{
		SCAN scan;
		char package [FILENAME_MAX];
		char scratch [FILENAME_MAX];
		char buffer [TEXTLINE_MAX];
		size_t line;
		scaninput (& scan, buffer, sizeof (buffer));
		for (line = 0; ~ fgetline (buffer, sizeof (buffer), stdin); line++)
		{
			scanwhile (& scan, gcsASCIIAlpha ".");
			scanbreak (& scan, ":");
			if (havetoken (& scan, "Name:"))
			{
				scanuntil (& scan, gcsBreak);
				extract (& scan, package, sizeof (package));
			}
			else if (havetoken (& scan, "Requires:"))
			{
				while (tokensize (& scan))
				{
					if (isclass (& scan, "A"))
					{
						extract (& scan, scratch, sizeof (scratch));
						printf ("\"%s\",\"%s\"\n", package, scratch);
					}
					nexttoken (& scan);
				}
			}
			else if (havetoken (& scan, "Requires.private:"))
			{
				while (tokensize (& scan))
				{
					if (isclass (& scan, "A"))
					{
						extract (& scan, scratch, sizeof (scratch));
						printf ("\"%s\",\"%s\"\n", package, scratch);
					}
					nexttoken (& scan);
				}
			}
			scanreset (& scan);
		}
	}
	return;
}

/*====================================================================*
 *
 *   void findfile (FIND *find, flag_t flags);
 *
 *   assume file is a directory; open the directory and test each one
 *   but ignore "." and ".." files;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void findfile (FIND * find, flag_t flags)

{
	struct dirent * dirent;
	char * filename = find->fullname;
	DIR * dir = opendir (filename);
	if (dir == (DIR *) (0))
	{
		testfile (find, flags);
		return;
	}
	while (* filename != (char) (0))
	{
		filename++;
	}
	* filename = PATH_C_EXTENDER;
	while ((dirent = readdir (dir)) != (struct dirent *) (0))
	{
		strcpy (filename +  1, dirent->d_name);
		partpath (find->fullname, find->pathname, find->filename);
		partfile (find->filename, find->basename, find->extender);
		testfile (find, flags);
	}
	* filename = (char) (0);
	closedir (dir);
	return;
}

/*====================================================================*
 *
 *   void testfile (FIND *find, flag_t flags);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void testfile (FIND * find, flag_t flags)

{
	if (lstat (find->fullname, & find->statinfo))
	{
		error (0, errno, "%s", find->fullname);
		return;
	}
	if (S_ISDIR (find->statinfo.st_mode))
	{
		char const * filename = find->filename;
		if (* filename == '.')
		{
			filename++;
		}
		if (* filename == '.')
		{
			filename++;
		}
		if (* filename == (char) (0))
		{
			return;
		}
		if (flags & (FIND_B_RECURSE))
		{
			findfile (find, flags);
		}
		return;
	}
	if (S_ISREG (find->statinfo.st_mode))
	{
		function (find, flags);
		return;
	}
	if (S_ISLNK (find->statinfo.st_mode))
	{
		function (find, flags);
		return;
	}
	return;
}

/*====================================================================*
 *
 *   int main (int argc, char const * argv[]);
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
		"rb",
		PUTOPTV_S_DIVINE,
		"convert pkgconfig dependency information to CSV dependency format",
		"r\trecursive search",
		(char const *) (0)
	};
	char const * paths [MAX_PATHS];
	char * buffer = (char *) (0);
	size_t index;
	flag_t flags = (flag_t) (0);
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'r':
			_setbits (find.flagword, FIND_B_RECURSE);
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		buffer = strdup (getenv ("PKG_CONFIG_PATH"));
		strsplit (paths, MAX_PATHS, buffer, PATH_C_SEPARATOR);
		for (index = 0; paths [index] != (char const *) (0); index++)
		{
			strcpy (find.fullname, paths [index]);
			strcpy (find.wildcard, "*.pc");
			find.pathname [0] = (char) (0);
			find.filename [0] = (char) (0);
			find.basename [0] = (char) (0);
			find.extender [0] = (char) (0);
			findfile (& find, flags);
		}
	}
	while ((argc) && (* argv))
	{
		strcpy (find.fullname, * argv);
		strcpy (find.wildcard, "*.pc");
		find.pathname [0] = (char) (0);
		find.filename [0] = (char) (0);
		find.basename [0] = (char) (0);
		find.extender [0] = (char) (0);
		findfile (& find, flags);
		argc--;
		argv++;
	}
	exit (0);
}

