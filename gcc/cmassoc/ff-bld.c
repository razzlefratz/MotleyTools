/*====================================================================*
 *
 *   ffb.c - build file test script generator;
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
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
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
#include "../files/match.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#include "../files/makefind.c"
#include "../files/showfind.c"
#include "../files/partpath.c"
#include "../files/partfile.c"
#include "../files/find.c"
#endif

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

static unsigned files = 0;

/*====================================================================*
 *
 *   static void testfile (FIND * find, flag_t flags);
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void testfile (FIND * find, flag_t flags)

{
	if (match (find->filename, find->wildcard))
	{
		printf ("elif [ %s -ot ${log} ]; then\n", find->fullname);
		printf ("\techo install %d failed >> ${log}\n", ++ files);
	}
	return;
}

/*====================================================================*
 *
 *   static void testfile (FIND * find, flag_t flags);
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void testlink (FIND * find, flag_t flags)

{
	if (match (find->filename, find->wildcard))
	{
		FIND link;
		memcpy (& link, find, sizeof (link));
		memset (link.filename, 0, sizeof (link.filename));
		readlink (link.fullname, link.filename, sizeof (link.filename));
		makepath (link.fullname, link.pathname, link.filename);
		printf ("elif [ ! %s -ef %s ]; then\n", link.fullname, find->fullname);
		printf ("\techo install %d failed >> ${log}\n", ++ files);
	}
	return;
}

/*====================================================================*
 *
 *   static unsigned function (FIND *find);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void findfile (FIND * find, flag_t flags)

{
	DIR * dir;
	struct dirent * dirent;
	char * filename;
	if ((dir = opendir (find->fullname)) == (DIR *) (0))
	{
		error (0, errno, "%s", find->fullname);
		return;
	}
	strcpy (find->pathname, find->fullname);
	for (filename = find->fullname; * filename; filename++);
	* filename = PATH_C_EXTENDER;
	while ((dirent = readdir (dir)))
	{
		strcpy (filename +  1, dirent->d_name);
		partpath (find->fullname, find->pathname, find->filename);
		partfile (find->filename, find->basename, find->extender);
		if (lstat (find->fullname, & find->statinfo))
		{
			error (0, errno, "%s", find->fullname);
		}
		else if (S_ISDIR (find->statinfo.st_mode))
		{
			char * filename = find->filename;
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
				continue;
			}

#ifdef NEVEREVERINAMILLIONYEARS

			if (_anyset (find->flagword, FIND_B_DIR))
			{
				testfile (find, flags);
			}

#endif

			if (_anyset (find->flagword, FIND_B_RECURSE))
			{
				findfile (find, flags);
			}
		}
		else if (S_ISREG (find->statinfo.st_mode))
		{
			if (_anyset (find->flagword, FIND_B_REG))
			{
				testfile (find, flags);
			}
		}
		else if (S_ISLNK (find->statinfo.st_mode))
		{
			if (_anyset (find->flagword, FIND_B_LNK))
			{
				testlink (find, flags);
			}
		}
	}
	* filename = (char) (0);
	closedir (dir);
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
		"print build file confirmation script",
		"findspec [> stdout]",
		"rb",
		"r\tresursive search",
		(char const *) (0)
	};
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
			exit (1);
		}
	}
	argc -= optind;
	argv += optind;
	if (_allclr (find.flagword, (FIND_B_REG | FIND_B_LNK)))
	{
		_setbits (find.flagword, (FIND_B_REG | FIND_B_LNK));
	}
	while ((argc) && (* argv))
	{
		makefind (& find, * argv);
		strcpy (find.fullname, find.pathname);
		findfile (& find, flags);
		argc--;
		argv++;
	}
	exit (0);
}

