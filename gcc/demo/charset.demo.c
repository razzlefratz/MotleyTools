/*====================================================================*
 *
 *   charset.demo.c - display command line character set expressions;
 *
 *   read command line arguments, treat them as character set expressions
 *   and write them to stdout;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include "../tools/tools.h"
#include "../chrlib/charset.c"

int main (int argc, char const *argv []) 

{
	char buffer [_LINESIZE];
	printf ("\n");
	for (argc = 0; argv [argc]; ++argc) 
	{
		printf ("[%s][%s]\n", argv [argc], charset (argv [argc], NUL, buffer, _LINESIZE));
	}
	printf ("\n");
	return (0);
}

