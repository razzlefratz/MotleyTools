/*====================================================================*
 *
 *   argv.c - display argument vector;
 *
 *   this program is a simple debugging tool that displays the argument
 *   vector argv[] on stdout for inspection.
 *
 *   use it to see how your host system processes command line arguments;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>

int main (int argc, char const * argv [])

{
	char const ** argp;
	for (argp = argv; * argp; argp++)
	{
		printf (" argv[%lu] = [%s]\n", (long unsigned)(argp - argv), * argp);
	}
	printf (" argv[%lu] = NULL\n", (long unsigned)(argp - argv));
	return (0);
}

