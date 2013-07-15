/*====================================================================*
 *
 *   purge.c - purge directory structure; 
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
#include "../files/match.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#include "../files/makefind.c"
#include "../files/partpath.c"
#include "../files/partfile.c"
#include "../files/find.c"
#endif

/*====================================================================*
 *   program functions;         
 *--------------------------------------------------------------------*/

static void findfile (FIND * find, flag_t flags); 
static void testfile (FIND * find, flag_t flags); 

/*====================================================================*
 *
 *   void function (struct _find_ * find, flag_t flags);
 *
 *   display and/or remove a file or link based on criteria in struct 
 *   search, including the pathname, wildcard and flagword;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (struct _find_ * find, flag_t flags) 

{ 
	if (!match (find->filename, find->wildcard)) 
	{ 
		return; 
	} 
	if (find->statinfo.st_mtime < find->filetime) 
	{ 
		if (remove (find->fullname) == - 1) 
		{ 
			if (_anyset (flags, FIND_B_ERRORS)) 
			{ 
				error (0, errno, "cannot remove %s", find->fullname); 
			} 
		} 
		else 
		{ 
			if (_anyset (flags, FIND_B_EVENTS)) 
			{ 
				error (0, 0, "%s", find->fullname); 
			} 
		} 
	} 
	return; 
} 

/*====================================================================*
 *
 *   void testfile (FIND * find, flag_t flags);
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
		if (_anyset (find->flagword, FIND_B_RECURSE)) 
		{ 
			findfile (find, flags); 
		} 
		if (_anyset (find->flagword, FIND_B_DIR)) 
		{ 
			function (find, flags); 
		} 
		return; 
	} 
	if (S_ISLNK (find->statinfo.st_mode)) 
	{ 
		if (_anyset (find->flagword, FIND_B_LNK)) 
		{ 
			function (find, flags); 
		} 
		return; 
	} 
	if (S_ISREG (find->statinfo.st_mode)) 
	{ 
		if (_anyset (find->flagword, FIND_B_REG)) 
		{ 
			function (find, flags); 
		} 
		return; 
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
	DIR * dir; 
	char * filename = find->fullname; 
	if ((dir = opendir (filename))) 
	{ 
		struct dirent * dirent; 
		while (* filename) 
		{ 
			filename++; 
		} 
		* filename = PATH_C_EXTENDER; 
		while ((dirent = readdir (dir))) 
		{ 
			strcpy (filename + 1, dirent->d_name); 
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
		"o:qrv", 
		PUTOPTV_S_SEARCH, 
		"remove selected files and links from finds and subfinds", 
		"o n\tif over (n) days old [0]", 
		"q\tquiet (don't report failures)", 
		"r\trecursive search", 
		"v\tverbose (report successes)", 
		(char const *) (0)
	}; 
	flag_t flags = (flag_t) (0); 
	signed c; 
	time (& find.filetime); 
	while ((c = getoptv (argc, argv, optv)) != - 1) 
	{ 
		switch (c) 
		{ 
		case 'o': 
			find.filetime -= uintspec (optarg, 1, DAYS_IN_YEAR) * SECONDS_IN_DAY; 
			find.filetime -= find.filetime % SECONDS_IN_DAY; 
			find.filetime += SECONDS_IN_DAY; 
			break; 
		case 'r': 
			_setbits (find.flagword, FIND_B_RECURSE); 
			break; 
		case 'q': 
			_clrbits (flags, FIND_B_ERRORS); 
			break; 
		case 'v': 
			_setbits (flags, FIND_B_EVENTS); 
			break; 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 
	if (_allclr (find.flagword, (FIND_B_LNK | FIND_B_REG))) 
	{ 
		_setbits (find.flagword, (FIND_B_LNK | FIND_B_REG)); 
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

