/*====================================================================*
 *
 *   chperm.c - change folder and file permissions;
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
#include <dirent.h>
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
#include "../tools/modespec.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../files/match.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#include "../files/partpath.c"
#include "../files/makefind.c"
#include "../files/partpath.c"
#include "../files/partfile.c"
#include "../files/find.c"
#endif

/*====================================================================*
 *   program constants
 *--------------------------------------------------------------------*/

#define CHPERM_B_RECURSE (1 << 0)
#define CHPERM_B_TESTRUN (1 << 1)
#define CHPERM_B_EVENTS  (1 << 2)
#define CHPERM_B_ERRORS  (1 << 3)

/*====================================================================*
 *
 *   static void findfile (FIND *find);
 *
 *   remove selected files and links from folders and subfolder;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void findfile (FIND * find, mode_t dirmode, mode_t regmode, flag_t flags)

{
	DIR * dir;
	if ((dir = opendir (find->fullname)))
	{
		struct dirent * dirent;
		char * filename;
		for (filename = find->fullname; * filename; filename++);
		* filename = PATH_C_EXTENDER;
		while ((dirent = readdir (dir)))
		{
			strcpy (filename +  1, dirent->d_name);
			if (lstat (find->fullname, & find->statinfo))
			{
				error (0, 0, "can't stat %s.", find->fullname);
				continue;
			}
			if (S_ISDIR (find->statinfo.st_mode))
			{
				char * sp = dirent->d_name;
				if (* sp == '.')
				{
					sp++;
				}
				if (* sp == '.')
				{
					sp++;
				}
				if (* sp == (char) (0))
				{
					continue;
				}
				if (flags & (CHPERM_B_RECURSE))
				{
					findfile (find, dirmode, regmode, flags);
				}
				if (flags & (CHPERM_B_TESTRUN))
				{
					printf ("change %s\n", find->fullname);
				}
				else if (chmod (find->fullname, dirmode))
				{
					error (0, 0, "can't change %s", find->fullname);
				}
				else if (flags & (CHPERM_B_EVENTS))
				{
					error (0, 0, "changed %s", find->fullname);
				}
				continue;
			}
			if (S_ISREG (find->statinfo.st_mode))
			{
				if (flags & (CHPERM_B_TESTRUN))
				{
					printf ("change %s\n", find->fullname);
				}
				else if (chmod (find->fullname, regmode))
				{
					error (0, 0, "can't change %s", find->fullname);
				}
				else if (flags & (CHPERM_B_EVENTS))
				{
					error (0, 0, "changed %s", find->fullname);
				}
				continue;
			}
		}
		* filename = (char) (0);
		closedir (dir);
	}
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
		"d:f:rv",
		PUTOPTV_S_SEARCH,
		"set folder and file permissions",
		"d m\tdirectory permission is m [0755]",
		"f m\tfile permission is m [0664]",
		"r\trecursive search",
		"v\tverbose messages",
		(char const *)(0)
	};
	mode_t dirmode = S_ISGID | S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
	mode_t regmode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
	flag_t flags = (flag_t) (0);
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'd':
			dirmode = modespec (optarg);
			break;
		case 'f':
			regmode = modespec (optarg);
			break;
		case 'r':
			_setbits (flags, CHPERM_B_RECURSE);
			break;
		case 'v':
			_setbits (flags, CHPERM_B_EVENTS);
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	while ((argc) && (* argv))
	{
		makefind (& find, * argv);
		findfile (& find, dirmode, regmode, flags);
		argc--;
		argv++;
	}
	exit (0);
}

