/*====================================================================*
 *
 *   log.c - multiple file log utility 
 *
 *   read from stdin and write to stdout and to each named file; this
 *   program is similar to tee which is essentially cat in reverse;
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

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#endif

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"a",
		"[file] [file] [> stdout]",
		"write stdin to stdout plus named files",
		"a\tappend output to files",
		(char const *)(0)
	};
	char buffer [TEXTLINE_MAX];
	char * openmode = "wb";
	FILE * files [argc];
	size_t file = 0;
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'a':
			openmode = "ab";
			break;
		case 'w':
			openmode = "wb";
			break;
		default:
			break;
		}
	}
	argc-= optind;
	argv+= optind;
	files [file++] = stdout;
	while ((argc) && (* argv)) 
	{
		files [file] = fopen (* argv, openmode);
		if (!files [file++]) 
		{
			error (0, errno, FILE_CANTOPEN, * argv);
			file--;
		}
		argc--;
		argv++;
	}
	files [file] = (FILE *) (0);
	while (fgets (buffer, sizeof (buffer), stdin)) 
	{
		for (file = 0; files [file]; file++) 
		{
			fputs (buffer, files [file]);
		}
	}
	exit (0);
}

