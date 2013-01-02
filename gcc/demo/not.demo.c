/*====================================================================*
 *
 *   not.c - convert and echo command vector argument;
 *
 *   this program demonstrates the difference between logical not (!) 
 *   and bitwise not (~) operations; it can be used as a teaching aid
 *   or a handy programming tool; 
 *
 *   command line arguments are converted to integers and printed
 *   along with its their ! and ~ conversions;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char const *argv []) 

{
	int argn;
	int value;
	for (argn = 1; argn < argc; argn++) 
	{
		value = atoi (argv [argn]);
		printf ("value=(%6d) !value=(%4x) ~value=(%4x)\n", value, !value, ~value);
	}
	printf ("TRUE=(%d) FALSE=(%d)\n", argn > 0, argn < 0);
	printf ("!(char *)(0)=(%d)\n", !(char *) (0));
	printf ("done\n");
	return (0);
}

