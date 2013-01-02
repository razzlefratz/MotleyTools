/*====================================================================*
 *
 *   ini.c - ; 
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
#include <string.h>
#include <ctype.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/tools.h"
#include "../tools/putopt.h"
#include "../tools/getopt.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#include "../tools/getopt.c"
#include "../tools/putopt.c"
#include "../tools/efreopen.c"
#include "../tools/profile.c"

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const *argv []) 

{
	static char const *usage [] = 
	{
		"h",
		"profile section element",
		"inspect or test profile",
		"h\thelp summary",
		(char *) (0)
	};
	char const *sp;
	signed c;
	optind = 1;
	opterr = 1;
	while ((c = getopt (argc, argv, usage [PUTOPT_I_OPTIONS])) != -1) 
	{
		switch (c) 
		{
		case 'h':
			putopt (usage);
			exit (0);
		default:
			exit (1);
		}
	}
	sp = profilestring ("/etc/cmassoc/cmassoc.ini", basename (argv [0]), "etcdir", "xxx");
	printf ("[%s]\n", sp);
	if (argc != 5) 
	{
		fprintf (stderr, "need 5 arguments.\n");
		exit (1);
	}
	printf ("[%s]\n%s=%s\n", argv [2], argv [3], profilestring (argv [1], argv [2], argv [3], argv [4]));
	exit (0);
}

