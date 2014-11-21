/*====================================================================*
 *
 *   ff.c - find file utility;
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
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <libgen.h>
#include <time.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../strlib/strlib.h"
#include "../chrlib/chrlib.h"
#include "../date/date.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/emalloc.c"
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#include "../files/makefind.c"
#include "../files/showfind.c"
#include "../files/partpath.c"
#include "../files/partfile.c"
#include "../files/match.c"
#include "../files/find.c"
#endif

#ifndef MAKEFILE
#include "../date/datecomp.c"
#include "../date/timecomp.c"
#endif

#ifndef MAKEFILE
#include "../strlib/strsplit.c"
#endif

#ifndef MAKEFILE
#include "../chrlib/chrcount.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define FF_TIMER 1
#define FF_OLDER 0
#define FF_NEWER 1

/*====================================================================*
 *   functions;
 *--------------------------------------------------------------------*/

static void findfile (FIND * find, flag_t flags);
static void testfile (FIND * find, flag_t flags);

/*====================================================================*
 *
 *   void showfile (FIND * find, flag_t flags);
 *
 *   determine if the find basename matches the find wildcard; if so
 *   the print the find.fullname, pathname or basename depending on
 *   the flags; optionally, prefix each print line with the file date;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void showfile (FIND * find, flag_t flags)

{
	if (match (find->filename, find->wildcard))
	{
		if (find->flagword & (FIND_B_DATETIME))
		{
			char datetime [LOGTIME_LEN];
			strftime (datetime, sizeof (datetime), LOGTIME, localtime (& find->statinfo.st_mtime));
			printf ("%s ", datetime);
		}
		if (find->flagword & (FIND_B_FILESIZE))
		{

#if defined (__APPLE__)

			printf ("%12llu ", find->statinfo.st_size);

#else

			printf ("%12lu ", find->statinfo.st_size);

#endif

		}
		switch (find->flagword & (FIND_B_PATHNAME | FIND_B_FILENAME))
		{
		case FIND_B_PATHNAME:
			printf ("%s\n", find->pathname);
			break;
		case FIND_B_FILENAME:
			printf ("%s\n", find->filename);
			break;
		default: 
			printf ("%s\n", find->fullname);
			break;
		}
	}
	return;
}

/*====================================================================*
 *
 *   void testfile (FIND * find, flag_t flags);
 *
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
		if (_anyset (find->flagword, FIND_B_DIR))
		{
			showfile (find, flags);
		}
		if (_anyset (find->flagword, FIND_B_RECURSE))
		{
			findfile (find, flags);
		}
		return;
	}
	if (S_ISLNK (find->statinfo.st_mode))
	{
		if (_anyset (find->flagword, FIND_B_LNK))
		{
			showfile (find, flags);
		}
		return;
	}
	if (S_ISREG (find->statinfo.st_mode))
	{
		if (_anyset (find->flagword, FIND_B_REG))
		{
			showfile (find, flags);
		}
		return;
	}
	return;
}

/*====================================================================*
 *
 *   void findfile (FIND * find, flag_t flags);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void findfile (FIND * find, flag_t flags)

{
	DIR * dir;
	char * filename = find->fullname;
	if ((dir = opendir (filename)))
	{
		struct dirent * dirent;
		while (* filename != (char) (0))
		{
			filename++;
		}
		* filename = PATH_C_EXTENDER;
		while ((dirent = readdir (dir)))
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
	testfile (find, flags);
	return;
}

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv [])

{
	extern FIND find;
	static char const * optv [] =
	{

#if FF_TIMER

		"defn:o:prstE:PSBLIK",

#else

		"defprstE:PSBLIK",

#endif

		PUTOPTV_S_SEARCH,
		"search folders and/or standard paths for files",
		"d\tprint date and time",
		"e\tprint search pathstring",
		"f\tprint filenames only",

#if FF_TIMER

		"n n\tif newer than (n) days [" LITERAL (FF_NEWER) "]",
		"o n\tif older than (n) days [" LITERAL (FF_OLDER) "]",

#endif

		"p\tprint pathnames only",
		"r\trecursive search",
		"s\tprint file size",
		"E s\tsearch environment string ${s}",
		"P\tsearch environment string ${PATH}",
		"S\tsearch system folders",
		"B\tsearch binary folders",
		"L\tsearch library folders",
		"I\tsearch include folders",
		(char const *) (0)
	};
	char * string = "";
	char const ** folders = (char const **) (0);
	char const ** folder = (char const **) (0);
	size_t count = 0;
	flag_t flags = (flag_t) (0);
	signed c;
	time (& find.filetime);
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'B':
			string = strdup (PATH_BINDIRS);
			break;
		case 'd':
			_setbits (find.flagword, FIND_B_DATETIME);
			break;
		case 'e':
			_setbits (flags, FIND_B_TESTRUN);
			break;
		case 'E':
			if ((string = getenv (optarg)))
			{
				error (0, EINVAL, "symbol ${%s} is not defined", optarg);
			}
			break;
		case 'f':
			_clrbits (find.flagword, FIND_B_PATHNAME);
			_setbits (find.flagword, FIND_B_FILENAME);
			break;
		case 'I':
			string = strdup (PATH_INCDIRS);
			break;
		case 'L':
			string = strdup (PATH_LIBDIRS);
			break;

#if FF_TIMER

		case 'n':
			find.filetime -= uintspec (optarg, 1, DAYS_IN_YEAR) * SECONDS_IN_DAY;
			find.filetime -= find.filetime % SECONDS_IN_DAY;
			find.filetime += SECONDS_IN_DAY;
			break;
		case 'o':
			find.filetime -= uintspec (optarg, 1, DAYS_IN_YEAR) * SECONDS_IN_DAY;
			find.filetime -= find.filetime % SECONDS_IN_DAY;
			find.filetime += SECONDS_IN_DAY;
			break;

#endif

		case 'p':
			_setbits (find.flagword, FIND_B_PATHNAME);
			_clrbits (find.flagword, FIND_B_FILENAME);
			break;
		case 'P':
			string = getenv ("PATH");
			break;
		case 'r':
			_setbits (find.flagword, FIND_B_RECURSE);
			break;
		case 's':
			_setbits (find.flagword, FIND_B_FILESIZE);
			break;
		case 'S':
			string = strdup (PATH_SYSDIRS);
			break;
		case 't':
			_setbits (find.flagword, FIND_B_TRAVERSE);
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (_anyset (flags, FIND_B_TESTRUN))
	{
		printf ("%s\n", string);
		exit (0);
	}
	if (_allclr (find.flagword, (FIND_B_DIR | FIND_B_LNK | FIND_B_REG)))
	{
		_setbits (find.flagword, (FIND_B_DIR | FIND_B_LNK | FIND_B_REG));
	}
	if ((string) && (* string))
	{
		count = 2 +  chrcount (string, PATH_C_SEPARATOR);
		folders = (char const **) (emalloc (count * sizeof (char const *)));
		strsplit (folders, count, string, PATH_C_SEPARATOR);
	}
	while ((argc) && (* argv))
	{
		makefind (& find, * argv);
		if (folders)
		{
			for (folder = folders; * folder; folder++)
			{
				if (! strcmp (* folder, "~"))
				{
					continue;
				}
				strcpy (find.fullname, * folder);
				strcpy (find.pathname, * folder);
				findfile (& find, flags);
			}
		}
		else 
		{
			strcpy (find.fullname, find.pathname);
			findfile (& find, flags);
		}
		argc--;
		argv++;
	}
	exit (0);
}

