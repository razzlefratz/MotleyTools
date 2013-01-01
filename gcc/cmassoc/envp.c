/*====================================================================*
 *
 *   envp.c - display environment vector;
 *
 *   this program is a simple debugging tool that displays the environment
 *   vector envp[] on stdout for inspection.
 *
 *   use it to see how your host system presents environment variables;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>

int main (int argc, char const * argv [], char const * envp []) 

{
	char const ** argp;
	for (argp = envp; *argp; argp++) 
	{
		printf (" envp[%lu] = [%s]\n", (long unsigned)(argp - envp), *argp);
	}
	printf (" envp[%lu] = NULL\n", (long unsigned)(argp - envp));
	return (0);
}

