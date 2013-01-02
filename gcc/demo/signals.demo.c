/*====================================================================*
 *
 *   signals.demo.c - 
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

#include "../linux/signals.c"

int main (int argc, char const *argv []) 

{
	char const *string;
	signed number;
	printf ("\n");
	for (argc = 1; argv [argc]; ++argc) 
	{
		number = signalcode (argv [argc]);
		string = signalname (number);
		printf (" argv[%2d] = [%s] %d %s \n", argc, argv [argc], number, string);
	}
	printf ("\n");
	return (0);
}

