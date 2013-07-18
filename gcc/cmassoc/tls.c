/*====================================================================*
 *
 *   tls.c - directory hierarchy display;
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

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#include "../tools/indent.c"
#include "../tools/error.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define DEPTH 3

/*====================================================================*
 *
 *   void function (char const * path, char * file, signed depth);
 *
 *   list directory structure on stdout; 
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (char const * path, char * file, unsigned depth) 

{ 
	DIR * dir; 
	static unsigned level = 0; 
	if (level > depth) 
	{ 
		return; 
	} 
	indent (level++, "%s", file); 
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
			if (stat (path, & statinfo)) 
			{ 
				error (0, errno, "%s", path); 
				continue; 
			} 
			if (S_ISDIR (statinfo.st_mode)) 
			{ 
				function (path, file, depth); 
				continue; 
			} 
			if (S_ISREG (statinfo.st_mode)) 
			{ 
				continue; 
			} 
			if (S_ISLNK (statinfo.st_mode)) 
			{ 
				continue; 
			} 
		} 
		* -- file = (char) (0); 
		closedir (dir); 
	} 
	level--; 
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
		"n:", 
		"path [path] [...] [> stdout]", 
		"print folder hierarchy on stdout", 
		"n n\tshow n levels [" LITERAL (DEPTH) "]", 
		(char const *) (0)
	}; 
	char filename [FILENAME_MAX]; 
	unsigned depth = DEPTH; 
	signed c; 
	while (~ (c = getoptv (argc, argv, optv))) 
	{ 
		switch (c) 
		{ 
		case 'n': 
			depth = (unsigned)(uintspec (optarg, 1, FILE_DIR_MAX)); 
			break; 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 
	if (!argc) 
	{ 
		strcpy (filename, getenv ("PWD")); 
		function (filename, filename, depth); 
	} 
	while ((argc) && (* argv)) 
	{ 
		strcpy (filename, * argv); 
		function (filename, filename, depth); 
		argc--; 
		argv++; 
	} 
	exit (0); 
} 

