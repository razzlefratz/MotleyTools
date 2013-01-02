/*====================================================================*
 *
 *   match.demo.c - 
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
#include "../files/match.c"
#endif

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const *argv []) 

{
	static char const *optv [] = 
	{
		"",
		"pattern literal [literal] [...] [> stdout]",
		"demonstrate the wildcard comparison function, match() ",
		(char const *)(0)
	};
	signed argn;
	signed c;
	optind = 1;
	opterr = 1;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	for (argn = 1; argn < argc; argn++) 
	{
		if (match (argv [argn], argv [0])) 
		{
			printf ("[%s] == [%s]\n", argv [0], argv [argn]);
		}
		else 
		{
			printf ("[%s] != [%s]\n", argv [0], argv [argn]);
		}
	}
	exit (0);
}

