/*====================================================================*
 *
 *   findpath.demo.c - 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/getopt.h"
#include "../tools/tools.h"
#include "../files/files.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/efreopen.c"
#include "../tools/eprintf.c"
#include "../tools/eperror.c"
#include "../tools/emalloc.c"
#include "../files/makefind.c"
#include "../files/showfind.c"
#include "../files/partpath.c"
#include "../files/partfile.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#endif

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const *argv []) 

{
	static char const *optv [] = 
	{
		"h",
		"findspec [ findspec [ ... ] ] [> stdout]",
		"demonstrate pathname expansion function, findpath() ",
		"h\thelp summary ",
		NULL
	};
	struct _find_ find;

// signed argn;

	signed c;
	optind = 1;
	opterr = 1;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case ':':
			exit (1);
		case '?':
			exit (1);
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	while ((argc-- > 0) && (*argv != (char *)(0))) 
	{
		makefind (&find, *argv++, FIND_M_NORMAL);
		showfind (&find, stdout);
	}
	exit (0);
}

