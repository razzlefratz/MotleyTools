/*====================================================================*
 *
 *   sweep.c - clean parallel directory structure;
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
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define SWEEP_S_COMMAND "install -m 0755 -o root -g root"
#define SWEEP_B_COMMAND (1 << 0)
#define SWEEP_B_REMOVE  (1 << 1)
#define SWEEP_B_FOLDERS (1 << 4)
#define SWEEP_B_RECURSE (1 << 2)
#define SWEEP_B_VERBOSE (1 << 3)

/*====================================================================*
 *
 *   void function (char const *thisfile, char const *thatfile, char const * command, flag_t flags);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (char const * thisfile, char const * thatfile, char const * command, flag_t flags)

{
	if (_anyset (flags, SWEEP_B_COMMAND))
	{
		printf ("%s %s %s\n", command, thisfile, thatfile);
	}
	else if (_allclr (flags, SWEEP_B_REMOVE))
	{
		printf ("%s also in %s\n", thisfile, thatfile);
	}
	else if (remove (thisfile))
	{
		error (0, 0, "can't remove %s", thisfile);
	}
	else if (_anyset (flags, SWEEP_B_VERBOSE))
	{
		error (0, 0, "removed %s", thisfile);
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

static void findfile (char * thispath, char * thatpath, char const * command, flag_t flags)

{
	DIR * dir;
	struct dirent * dirent;
	char * thisfile = thispath;
	char * thatfile = thatpath;
	struct stat this;
	struct stat that;
	if ((dir = opendir (thispath)))
	{
		while (* thisfile)
		{
			thisfile++;
		}
		while (* thatfile)
		{
			thatfile++;
		}
		* thisfile++ = PATH_C_EXTENDER;
		* thatfile++ = PATH_C_EXTENDER;
		while ((dirent = readdir (dir)))
		{
			strcpy (thisfile, dirent->d_name);
			strcpy (thatfile, dirent->d_name);
			if (stat (thatpath, & that))
			{
				error (0, 0, "can't stat %s", thatpath);
				continue;
			}
			if (stat (thispath, & this))
			{
				error (0, 0, "can't stat %s", thispath);
				continue;
			}
			if (S_ISDIR (this.st_mode) && S_ISDIR (that.st_mode))
			{
				char * filename = dirent->d_name;
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
				if (_anyset (flags, SWEEP_B_RECURSE))
				{
					findfile (thispath, thatpath, command, flags);
				}
				function (thispath, thatpath, command, flags);
				continue;
			}
			if (S_ISREG (this.st_mode) && S_ISREG (that.st_mode))
			{
				function (thispath, thatpath, command, flags);
				continue;
			}
			if (S_ISLNK (this.st_mode) && S_ISLNK (that.st_mode))
			{
				function (thispath, thatpath, command, flags);
				continue;
			}

#if 0

			if (S_ISBLK (this.st_mode) && S_ISBLK (that.st_mode))
			{
				continue;
			}
			if (S_ISCHR (this.st_mode) && S_ISCHR (that.st_mode))
			{
				continue;
			}
			if (S_ISFIFO (this.st_mode) && S_ISFIFO (that.st_mode))
			{
				continue;
			}
			if (S_ISSOCK (this.st_mode) && S_ISBLK (that.st_mode))
			{
				continue;
			}

#endif

		}
		* -- thisfile = (char) (0);
		* -- thatfile = (char) (0);
		closedir (dir);
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
		"c:drxvC",
		"target-path source-path [source-path] ... [> stdout]",
		"remove files/folders from target-path that exist in any source-path.",
		"c s\tprint as system command s",
		"d\tremove folders (use with care)",
		"r\trecursive comparison",
		"x\tremove files",
		"v\tverbose messages",
		(char const *) (0)
	};
	char thispath [FILENAME_MAX +  1];
	char thatpath [FILENAME_MAX +  1];
	char const * command = SWEEP_S_COMMAND;
	flag_t flags = (flag_t) (0);
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'c':
			_setbits (flags, SWEEP_B_COMMAND);
			command = optarg;
			break;
		case 'x':
			_setbits (flags, SWEEP_B_REMOVE);
			break;
		case 'd':
			_setbits (flags, SWEEP_B_FOLDERS);
			break;
		case 'r':
			_setbits (flags, SWEEP_B_RECURSE);
			break;
		case 'v':
			_setbits (flags, SWEEP_B_VERBOSE);
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
		findfile (thispath, thatpath, command, flags);
		argc--;
		argv++;
	}
	exit (0);
}

