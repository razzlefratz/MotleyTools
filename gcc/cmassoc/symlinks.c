/*====================================================================*
 *
 *   symlinks.c - find and display active and broken symbolic links;
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
#include "../tools/console.c"
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

/*====================================================================*
 *   program constants; 
 *--------------------------------------------------------------------*/

#define LINK_B_ACTIVE (1 << 0)
#define LINK_B_BROKEN (1 << 1)
#define LINK_B_REPORT (1 << 2)
#define LINK_B_REMOVE (1 << 3)

/*====================================================================*
 *   program functions; 
 *--------------------------------------------------------------------*/

static void testfile (FIND * find, flag_t flags);
static void findfile (FIND * find, flag_t flags);

/*====================================================================*
 *
 *   void function (FIND *find, FIND * link, flag_t flags);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (FIND * find, FIND * link, flag_t flags) 

{
	if (match (find->filename, find->wildcard)) 
	{
		if (flags & LINK_B_REPORT) 
		{
			printf ("ln -fs %s %s\n", link->fullname, find->fullname);
		}
		else if ((flags & LINK_B_REMOVE) == 0) 
		{
			printf ("%s --> %s\n", find->fullname, link->fullname);
		}
		else if (unlink (find->fullname) != 0) 
		{
			error (0, errno, "%s --> %s", find->fullname, link->fullname);
		}
		else if (flags & FIND_B_VERBOSE) 
		{
			printf ("%s --> %s\n", find->fullname, link->fullname);
		}
	}
	return;
}


/*====================================================================*
 *
 *   void findfile (FIND *find, flag_t flags);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void findfile (FIND * find, flag_t flags) 

{
	struct dirent *dirent;
	char *filename = find->fullname;
	DIR *dir;
	if (!(dir = opendir (filename))) 
	{
		testfile (find, flags);
		return;
	}
	while (*filename != (char) (0)) 
	{
		filename++;
	}
	*filename = PATH_C_EXTENDER;
	while ((dirent = readdir (dir))) 
	{
		strcpy (filename + 1, dirent->d_name);
		partpath (find->fullname, find->pathname, find->filename);
		partfile (find->filename, find->basename, find->extender);
		testfile (find, flags);
	}
	*filename = (char) (0);
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
	if (lstat (find->fullname, &find->statinfo)) 
	{
		error (0, errno, "%s", find->fullname);
		return;
	}
	if (S_ISDIR (find->statinfo.st_mode)) 
	{
		char const *filename = find->filename;
		if (*filename == '.') 
		{
			filename++;
		}
		if (*filename == '.') 
		{
			filename++;
		}
		if (*filename == (char) (0)) 
		{
			return;
		}
		if (_anyset (find->flagword, FIND_B_RECURSE)) 
		{
			findfile (find, flags);
		}
		return;
	}
	if (S_ISLNK (find->statinfo.st_mode)) 
	{
		FIND link;
		memcpy (&link, find, sizeof (link));
		memset (link.filename, 0, sizeof (link.filename));
		readlink (link.fullname, link.filename, sizeof (link.filename));
		makepath (link.fullname, link.pathname, link.filename);
		if (_anyset (flags, LINK_B_ACTIVE)) 
		{
			if (!lstat (link.fullname, &link.statinfo)) 
			{
				function (find, &link, flags);
			}
			return;
		}
		if (_anyset (flags, LINK_B_BROKEN)) 
		{
			if (lstat (link.fullname, &link.statinfo)) 
			{
				function (find, &link, flags);
			}
			return;
		}
		function (find, &link, flags);
		return;
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
		"abcxrv",
		PUTOPTV_S_SEARCH,
		"search folders and subfolders for symbolic links",
		"a\tselect active links",
		"b\tselect broken links",
		"c\tprint 'ln' commands",
		"x\tremove selected links",
		"r\trecursive search",
		"v\tverbose messages",
		(char const *) (0)
	};
	flag_t flags = (flag_t) (0);
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'a':
			_setbits (flags, LINK_B_ACTIVE);
			break;
		case 'b':
			_setbits (flags, LINK_B_BROKEN);
			break;
		case 'c':
			_setbits (flags, LINK_B_REPORT);
			break;
		case 'x':
			_setbits (flags, LINK_B_REMOVE);
			break;
		case 'r':
			_setbits (find.flagword, FIND_B_RECURSE);
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
	while ((argc) && (* argv)) 
	{
		makefind (&find, * argv);
		findfile (&find, flags);
		argc--;
		argv++;
	}
	exit (0);
}

