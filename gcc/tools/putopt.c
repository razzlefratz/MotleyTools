/*====================================================================*
 *
 *   void putopt (char const *optv []);
 *
 *   putopt.h
 *
 *   print program information on stdout; informtion is stored as an
 *   ordered string vector; string indexes are defined in putopt.h;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef PUTOPT_SOURCE
#define PUTOPT_SOURCE

#include <stdio.h>
#include <stdlib.h>

#include "../tools/getopt.h"
#include "../tools/putopt.h"

void putopt (char const *optv []) 

{
	extern char const *program_name;
	size_t index;
	printf ("\n");
	printf (" purpose: %s\n\n", optv [PUTOPT_I_PURPOSE]);
	printf (" command: %s [options] %s\n\n", program_name, optv [PUTOPT_I_COMMAND]);
	printf (" options: [%s]\n\n", optv [PUTOPT_I_OPTIONS]);
	for (index = PUTOPT_I_DETAILS; optv [index] != (char *) (0); index++) 
	{
		printf (" %c%s\n", GETOPT_C_OPTION, optv [index]);
	}
	printf ("\n");
	return;
}


#endif

