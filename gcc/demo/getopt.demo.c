/*====================================================================*
 *
 *   getopt.demo.c - getopt test utility
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <stddef.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/getopt.h"
#include "../tools/putopt.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#endif

/*====================================================================*
 *   main program
 *--------------------------------------------------------------------*/

int main (int argc, char const *argv []) 

{
	static char const *optv [] = 
	{
		"abcx:y:z:XYZh",
		PUTOPT_S_DIVINE,
		"show value of extern getopt() variables",
		"e\ttoggle opterr between 0 and 1 ",
		(char const *)(0)
	};
	signed c;
	optind = 1;
	opterr = 1;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case '-':
		case 'a':
		case 'b':
		case 'c':
		case 'x':
		case 'y':
		case 'z':
		case 'X':
		case 'Y':
		case 'Z':
			printf ("optopt='%c' optarg=\"%s\"\n", optopt, optarg);
			break;
		case 'e':
			opterr = opterr? 0: 1;
			break;
		case 'h':
			putoptv (optv);
			exit (0);
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
	printf ("\n");
	printf ("argc=(%d)\n", argc);
	printf ("argv[optind]=\"%s\"\n", *argv);
	printf ("opterr=(%d)\n", opterr);
	printf ("optind=(%d)\n", optind);
	printf ("optopt=(%d)\n", optopt);
	printf ("optarg=[%s]\n", optarg);
	printf ("\n");
	while ((argc > 0) && (*argv != (char *)(0))) 
	{
		printf ("argv[%2d]=\"%s\"\n", argc--, *argv++);
	}
	exit (0);
}

