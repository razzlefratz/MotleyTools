/*====================================================================*
 *
 *   argv.c - display argument vector;
 *
 *   this program is a simple debugging tool that displays the argument
 *   vector argv[] on stdout for inspection.
 *
 *   use it to see how your host system processes command line arguments;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>

#include "../tools/truth.c"

int main (int argc, char const *argv []) 

{
	for (argc = 1; argv [argc]; ++argc) 
	{
		printf (" argv[%2d] = [%s] %d \n", argc, argv [argc], truth (argv [argc], -1));
	}
	printf ("\n");
	return (0);
}

