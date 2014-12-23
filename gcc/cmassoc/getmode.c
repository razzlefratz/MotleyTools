/*====================================================================*
 *
 *   getmode.c - print file name, type, mode, owner and group on stdout;
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
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../linux/linux.h"
#include "../files/files.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../files/match.c"
#include "../tools/fputn.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#include "../files/makefind.c"
#include "../files/partpath.c"
#include "../files/partfile.c"
#include "../linux/ftype.c"
#endif

/*====================================================================*
 *
 *   void function (FIND *find, flag_t flags);
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (FIND * find, flag_t flags)

{
	if (match (find->filename, find->wildcard))
	{
		fputc (ftypecode (find->statinfo.st_mode), stdout);
		fputc (ITEM_C_EXTENDER, stdout);
		fputn ((find->statinfo.st_mode >> FILE_MODE_BITS) & FILE_TYPE_MASK, 16, 4, stdout);
		fputc (ITEM_C_EXTENDER, stdout);
		fputn ((find->statinfo.st_mode >> 0) & FILE_MODE_MASK, 8, 4, stdout);
		fputc (ITEM_C_EXTENDER, stdout);
		fputn (find->statinfo.st_uid, 10, 5, stdout);
		fputc (ITEM_C_EXTENDER, stdout);
		fputn (find->statinfo.st_gid, 10, 5, stdout);
		fputc (ITEM_C_EXTENDER, stdout);
		fputs (find->fullname, stdout);
		fputc (LIST_C_EXTENDER, stdout);
		fputc ('\n', stdout);
	}
	return;
}

/*====================================================================*
 *
 *   void findfile (FIND *find);
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
	DIR * dir;
	if ((dir = opendir (find->fullname)) != (DIR *) (0))
	{
		struct dirent * dirent;
		char * filename;
		strcpy (find->pathname, find->fullname);
		for (filename = find->fullname; * filename; filename++);
		* filename = PATH_C_EXTENDER;
		while ((dirent = readdir (dir)))
		{
			strcpy (filename +  1, dirent->d_name);
			strcpy (find->filename, dirent->d_name);
			if (lstat (find->fullname, & find->statinfo))
			{
				error (0, errno, "can't stat %s", find->fullname);
			}
			else if (S_ISDIR (find->statinfo.st_mode))
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
				if (flags & (FIND_B_DIR))
				{
					function (find, flags);
				}
				if (flags & (FIND_B_RECURSE))
				{
					findfile (find, flags);
				}
			}
			else if (S_ISREG (find->statinfo.st_mode))
			{
				if (flags & (FIND_B_REG))
				{
					function (find, flags);
				}
			}
			else if (S_ISLNK (find->statinfo.st_mode))
			{
				if (flags & (FIND_B_LNK))
				{
					function (find, flags);
				}
			}

#ifdef NEEDED

			else if (S_ISBLK (find->statinfo.st_mode))
			{
				if (flags & (FIND_B_BLK))
				{
					function (find, flags);
				}
			}
			else if (S_ISCHR (find->statinfo.st_mode))
			{
				if (flags & (FIND_B_CHR))
				{
					function (find, flags);
				}
			}
			else if (S_ISFIFO (find->statinfo.st_mode))
			{
				if (flags & (FIND_B_FIFO))
				{
					function (find, flags);
				}
			}
			else if (S_ISSOCK (find->statinfo.st_mode))
			{
				if (flags & (FIND_B_SOCK))
				{
					function (find, flags);
				}
			}

#endif

		}
		* filename = (char) (0);
		closedir (dir);
	}
	else 
	{
		error (0, errno, "can't open %s", find->fullname);
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
		"rBCDFLRS",
		PUTOPTV_S_FUNNEL,
		"print file name, type, mode, owner and group on stdout",
		"r\trecursive search",
		(char const *) (0)
	};
	FIND find;
	flag_t flags = (flag_t) (0);
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'r':
			_setbits (flags, FIND_B_RECURSE);
			break;
		case 'D':
			_setbits (flags, FIND_B_DIR);
			break;
		case 'R':
			_setbits (flags, FIND_B_REG);
			break;
		case 'L':
			_setbits (flags, FIND_B_LNK);
			break;
		case 'B':
			_setbits (flags, FIND_B_BLK);
			break;
		case 'C':
			_setbits (flags, FIND_B_CHR);
			break;
		case 'F':
			_setbits (flags, FIND_B_FIFO);
			break;
		case 'S':
			_setbits (flags, FIND_B_SOCK);
			break;
		default: 
			exit (1);
		}
	}
	argc -= optind;
	argv += optind;
	if (_allclr (flags, FIND_B_ALL))
	{
		_setbits (flags, FIND_B_ALL);
	}
	while ((argc) && (* argv))
	{
		makefind (& find, * argv);
		findfile (& find, flags);
		argc--;
		argv++;
	}
	exit (0);
}

