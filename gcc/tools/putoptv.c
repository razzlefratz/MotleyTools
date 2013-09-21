/*====================================================================*
 *
 *   void putoptv (char const * optv []);
 *
 *   putoptv.h
 *
 *   print program information on stdout; informtion is stored as an
 *   ordered string vector; string indexes are defined in getopt.h;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef PUTOPTV_SOURCE
#define PUTOPTV_SOURCE

#include <stdio.h>
#include <stdlib.h>

#include "../tools/getoptv.h"
#include "../tools/putoptv.h"

void putoptv (char const * optv []) 

{
	extern char const * program_name;
	signed index;
	printf ("\n");
	printf (" program: %s\n\n", optv [PUTOPTV_I_PROGRAM]);
	printf (" command: %s [options] %s\n\n", program_name, optv [PUTOPTV_I_COMMAND]);
	printf (" options: [%s%c%c]\n\n", optv [PUTOPTV_I_OPTIONS], GETOPTV_C_VERSION, GETOPTV_C_SUMMARY);
	for (index = PUTOPTV_I_DETAILS; optv [index]; index++) 
	{
		printf (" %c%s\n", GETOPTV_C_OPTION, optv [index]);
	}
	printf (" %c%c\tversion information\n", GETOPTV_C_OPTION, GETOPTV_C_VERSION);
	printf (" %c%c\thelp summary\n", GETOPTV_C_OPTION, GETOPTV_C_SUMMARY);
	printf ("\n");
	return;
}


#endif

