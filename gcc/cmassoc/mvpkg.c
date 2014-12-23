/*====================================================================*
 *
 *   mvpkg.c - clean parallel directory structure;
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
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../files/files.h"
#include "../strlib/strlib.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/error.c"
#include "../tools/error_on_line.c"
#endif

#ifndef MAKEFILE
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#endif

#ifndef MAKEFILE
#include "../strlib/strpkgcmp.c"
#endif

/*====================================================================*
 *
 *   void function (char const *thisfile, char const *thatfile, flag_t flags);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void myrename (char const * thisfile, char const * thatfile, flag_t flags)

{
	if (flags & (FIND_B_TESTRUN))
	{
		error (0, 0, "mv %s %s\n", thisfile, thatfile);
	}
	else if (rename (thisfile, thatfile))
	{
		error (0, errno, "can't move %s to %s", thisfile, thatfile);
	}
	else if (flags & (FIND_B_VERBOSE))
	{
		error (0, 0, "mv %s to %s", thisfile, thatfile);
	}
	return;
}

/*====================================================================*
 *
 *   void function (char const *thisfile, char const *thatfile, flag_t flags);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void myremove (char const * thisfile, flag_t flags)

{
	if (flags & (FIND_B_TESTRUN))
	{
		error (0, 0, "rm %s\n", thisfile);
	}
	else if (remove (thisfile))
	{
		error (0, errno, "can't remove %s", thisfile);
	}
	else if (flags & (FIND_B_VERBOSE))
	{
		error (0, errno, "rm %s", thisfile);
	}
	return;
}

/*====================================================================*
 *
 *   void findfile (char *thispath, char *thatpath, flag_t flags);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void findfile (char thispathname [], char thatpathname [], flag_t flags)

{
	DIR * thisdir;
	DIR * thatdir;
	struct dirent * thisdirent;
	struct dirent * thatdirent;
	struct stat thisstatinfo;
	struct stat thatstatinfo;
	char * thisfilename;
	char * thatfilename;
	if ((thisdir = opendir (thispathname)) == (DIR *) (0))
	{
		error (0, errno, "%s", thispathname);
		return;
	}
	for (thisfilename = thispathname; * thisfilename != (char) (0); thisfilename++);
	* thisfilename = PATH_C_EXTENDER;
	while ((thisdirent = readdir (thisdir)))
	{
		strcpy (thisfilename +  1, thisdirent->d_name);
		if (lstat (thispathname, & thisstatinfo))
		{
			error (0, errno, "can't stat %s", thispathname);
		}
		else if (S_ISREG (thisstatinfo.st_mode))
		{
			if ((thatdir = opendir (thatpathname)) == (DIR *) (0))
			{
				error (0, errno, "%s", thatpathname);
				continue;
			}
			for (thatfilename = thatpathname; * thatfilename != (char) (0); thatfilename++);
			* thatfilename = PATH_C_EXTENDER;
			while ((thatdirent = readdir (thatdir)))
			{
				strcpy (thatfilename +  1, thatdirent->d_name);
				if (lstat (thatpathname, & thatstatinfo))
				{
					error (0, errno, "can't stat %s", thatpathname);
				}
				else if (S_ISDIR (thatstatinfo.st_mode))
				{
					continue;
				}
				else if (S_ISREG (thatstatinfo.st_mode))
				{
					int order = strpkgcmp (thisfilename, thatfilename, FILE_C_EXTENDER);
					if (order > 0)
					{
						strcpy (thatfilename +  1, thisdirent->d_name);
						myrename (thispathname, thatpathname, flags);
					}
					if (order == 0)
					{
						myremove (thispathname, flags);
					}
				}
			}
			* thatfilename = (char) (0);
			closedir (thatdir);
		}
	}
	thisfilename = (char) (0);
	closedir (thisdir);
	return;
}

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv [])

{
	static char const * optv [] =
	{
		"cvh",
		"sourcepath targetpath [targetpath] ... [> stdout]",
		"move like packages from current folder to a target folder.",
		"c\treport but do not remove anything",
		"v\tverbose messages",
		(char const *) (0)
	};
	char thispath [FILENAME_MAX];
	char thatpath [FILENAME_MAX];
	flag_t flags = (flag_t) (0);
	int c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'c':
			_setbits (flags, FIND_B_TESTRUN);
			break;
		case 'v':
			_setbits (flags, FIND_B_VERBOSE);
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (argc)
	{
		strcpy (thispath, * argv);
		argc--;
		argv++;
	}
	while ((argc) && (* argv))
	{
		strcpy (thatpath, * argv);
		findfile (thispath, thatpath, flags);
		argc--;
		argv++;
	}
	exit (0);
}

