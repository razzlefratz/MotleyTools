/*====================================================================*
 *
 *   import.c - import files; 
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
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../files/files.h"
#include "../date/date.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#include "../files/makefind.c"
#include "../files/partpath.c"
#include "../files/partfile.c"
#include "../files/find.c"
#include "../files/match.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define IMPORT_VERBOSE (1 << 0)
#define IMPORT_SILENCE (1 << 1)

/*====================================================================*
 *   program functions;         
 *--------------------------------------------------------------------*/

static void findfile (FIND * find, FIND * home, flag_t flags);
static void testfile (FIND * find, FIND * home, flag_t flags);

/*====================================================================*
 *
 *   void function (struct _find_ *find, flag_t flags);
 *
 *   display and/or remove a file or link based on criteria in struct 
 *   search, including the pathname, wildcard and flagword;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (struct _find_ * find, struct _find_ * home, flag_t flags) 

{
	char buffer [BUFSIZ];
	signed length;
	if (!match (find->filename, find->wildcard)) 
	{
		return;
	}
	strcpy (home->filename, find->filename);
	makepath (home->fullname, home->pathname, home->filename);
	if ((find->fd = open (find->fullname, O_RDONLY)) == -1) 
	{
		error (0, errno, FILE_CANTOPEN, find->fullname);
		return;
	}
	if ((home->fd = open (home->fullname, O_CREAT |O_WRONLY, find->statinfo.st_mode)) == -1) 
	{
		error (0, errno, FILE_CANTOPEN, home->fullname);
		close (find->fd);
		return;
	}
	if (_anyset (flags, IMPORT_VERBOSE)) 
	{
		printf ("%s\n", find->fullname);
	}
	while ((length = read (find->fd, buffer, sizeof (buffer))) > 0) 
	{
		if (write (home->fd, buffer, length) < length) 
		{
			error (0, errno, FILE_CANTSAVE, home->fullname);
			break;
		}
	}
	close (home->fd);
	close (find->fd);
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

static void testfile (FIND * find, FIND * home, flag_t flags) 

{
	if (lstat (find->fullname, & find->statinfo)) 
	{
		error (0, errno, FILE_CANTSTAT, find->fullname);
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
		if (_anyset (find->flagword, FIND_B_RECURSE)) 
		{
			findfile (find, home, flags);
		}
		if (_anyset (find->flagword, FIND_B_DIR)) 
		{
			function (find, home, flags);
		}
		return;
	}
	if (S_ISLNK (find->statinfo.st_mode)) 
	{
		if (_anyset (find->flagword, FIND_B_LNK)) 
		{
			function (find, home, flags);
		}
		return;
	}
	if (S_ISREG (find->statinfo.st_mode)) 
	{
		if (_anyset (find->flagword, FIND_B_REG)) 
		{
			function (find, home, flags);
		}
		return;
	}
	return;
}

/*====================================================================*
 *
 *   void findfile (FIND *find, FIND * home, flag_t flags);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void findfile (FIND * find, FIND * home, flag_t flags) 

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
		while ((dirent = readdir (dir)) != (struct dirent *) (0)) 
		{
			strcpy (filename + 1, dirent->d_name);
			partpath (find->fullname, find->pathname, find->filename);
			partfile (find->filename, find->basename, find->extender);
			testfile (find, home, flags);
		}
		* filename = (char) (0);
		closedir (dir);
		return;
	}
	testfile (find, home, flags);
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
		"o:qrv",
		"folder findspec [findspec] [...]",
		"copy remote files to local folder",
		"q\tquiet (don't report failures)",
		"r\trecursive search",
		"v\tverbose (report successes)",
		(char const *) (0)
	};
	FIND home;
	flag_t flags = (flag_t) (0);
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'r':
			_setbits (find.flagword, FIND_B_RECURSE);
			break;
		case 'q':
			_clrbits (flags, IMPORT_SILENCE);
			break;
		case 'v':
			_setbits (flags, IMPORT_VERBOSE);
			break;
		default:
			break;
		}
	}
	argc-= optind;
	argv+= optind;
	if (_allclr (find.flagword, (FIND_B_LNK | FIND_B_REG))) 
	{
		_setbits (find.flagword, (FIND_B_LNK | FIND_B_REG));
	}
	if (argc) 
	{
		strcpy (home.pathname, * argv);
		if (lstat (home.pathname, & home.statinfo)) 
		{
			error (1, errno, FILE_CANTSTAT, * argv);
		}
		if (!S_ISDIR (home.statinfo.st_mode)) 
		{
			error (1, EINVAL, "%s is not a folder", * argv);
		}
		argc--;
		argv++;
	}
	while ((argc) && (* argv)) 
	{
		makefind (& find, * argv);
		findfile (& find, & home, flags);
		argc--;
		argv++;
	}
	exit (0);
}

