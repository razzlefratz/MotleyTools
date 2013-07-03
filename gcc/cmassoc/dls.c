/*====================================================================*
 *
 *   dls.c - directory hierarchy display;
 *
 *   print a directory hierarchy on stdout using simple ascii text; 
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
#include "../linux/linux.h"
#include "../list/list.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#include "../tools/emalloc.c"
#include "../tools/erealloc.c"
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#endif

#ifndef MAKEFILE
#include "../list/listcreate.c"
#include "../list/listdelete.c"
#include "../list/listinsert.c"
#include "../list/listdetect.c"
#include "../list/listexpand.c"
#include "../list/listcolumn.c"
#endif

#ifndef MAKEFILE
#include "../linux/getviewport.c"
#endif

/*====================================================================*
 *  program constants;
 *--------------------------------------------------------------------*/

#define COUNT 0
#define WIDTH 0

/*====================================================================*
 *
 *   void function (char const * path, char *file, size_t width, size_t count, bool index, flag_t flags);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (char const * path, char * file, size_t width, size_t count, bool index, flag_t flags) 

{
	DIR * dir;
	LIST list;
	listcreate (& list, _LISTSIZE);
	printf ("%s\n", path);
	if ((dir = opendir (path))) 
	{
		struct dirent * dirent;
		struct stat statinfo;
		while (* file) 
		{
			file++;
		}
		* file++ = PATH_C_EXTENDER;
		while ((dirent = readdir (dir))) 
		{
			char const * sp = dirent->d_name;
			if (* sp == FILE_C_EXTENDER) 
			{
				sp++;
			}
			if (* sp == FILE_C_EXTENDER) 
			{
				sp++;
			}
			if (* sp == (char) (0)) 
			{
				continue;
			}
			strcpy (file, dirent->d_name);
			if (lstat (path, & statinfo)) 
			{
				error (0, errno, "%s", path);
				continue;
			}
			if (S_ISDIR (statinfo.st_mode)) 
			{
				if (flags & (FIND_B_DIR)) 
				{
					listinsert (& list, file);
				}
				continue;
			}
			if (S_ISLNK (statinfo.st_mode)) 
			{
				if (flags & (FIND_B_LNK)) 
				{
					listinsert (& list, file);
				}
				continue;
			}
			if (S_ISREG (statinfo.st_mode)) 
			{
				if (flags & (FIND_B_REG)) 
				{
					listinsert (& list, file);
				}
				continue;
			}
		}
		*--file = (char) (0);
		closedir (dir);
	}
	listcolumn (& list, stderr, width, count, index);
	listdelete (& list);
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
	static char const * optv [] = 
	{
		"c:dflnw:",
		"path [path] [...] [> stdout]",
		"list folders or links or standard files",
		"c n\tcolumn count is (n) [" LITERAL (COUNT) "]",
		"d\tlist directory files",
		"f\tlist standard files",
		"l\tlist symbolic links",
		"w n\tscreen width is (n) [" LITERAL (WIDTH) "]",
		"n\tnumber items",
		(char const *) (0)
	};
	char filename [FILENAME_MAX];
	bool index = false;
	flag_t flags = (flag_t) (0);
	size_t width = WIDTH;
	size_t count = COUNT;
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'd':
			_clrbits (flags, FIND_B_REG);
			_clrbits (flags, FIND_B_LNK);
			_setbits (flags, FIND_B_DIR);
			break;
		case 'l':
			_clrbits (flags, FIND_B_REG);
			_setbits (flags, FIND_B_LNK);
			_clrbits (flags, FIND_B_DIR);
			break;
		case 'f':
			_setbits (flags, FIND_B_REG);
			_clrbits (flags, FIND_B_LNK);
			_clrbits (flags, FIND_B_DIR);
			break;
		case 'n':
			index = true;
			break;
		case 'w':
			width = uintspec (optarg, 1, 132);
			break;
		case 'c':
			count = uintspec (optarg, 1, 16);
			break;
		default:
			break;
		}
	}
	argc-= optind;
	argv+= optind;
	if (_allclr (flags, (FIND_B_ALL))) 
	{
		_setbits (flags, FIND_B_DIR);
	}
	if (!argc) 
	{
		strcpy (filename, getenv ("PWD"));
		function (filename, filename, width, count, index, flags);
	}
	while ((argc) && (* argv)) 
	{
		strcpy (filename, * argv);
		function (filename, filename, width, count, index, flags);
		argc--;
		argv++;
	}
	exit (0);
}

