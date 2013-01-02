/*====================================================================*
 *
 *   getclass.demo.c -
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>

#include "getclass.c"

int main (int argc, char const *argv []) 

{
	char buffer [1000];
	size_t length = sizeof (buffer);
	size_t lineno = 0;
	char c;
	while ((c = getclass (buffer, length, &lineno, stdin, (void *)(getc), (void *)(ungetc))) != EOF) 
	{
		printf ("%d %c [%s]\n", lineno, c, buffer);
	}
	return;
}

