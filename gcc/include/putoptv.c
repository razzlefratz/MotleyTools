/*====================================================================*
 *
 *   void putoptv(char const *help[], signed status);
 *
 *   putopt.h
 *
 *   print program information on stderr; informtion is stored as an
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

void putoptv (char const *optv []) 

{
	extern char const *program_name;
	size_t index;
	fprintf (stderr, "\n");
	fprintf (stderr, " purpose: %s\n\n", optv [PUTOPTV_I_PURPOSE]);
	fprintf (stderr, " command: %s [options] %s\n\n", program_name, optv [PUTOPTV_I_COMMAND]);
	fprintf (stderr, " options: [%s%c%c]\n\n", optv [PUTOPTV_I_OPTIONS], GETOPT_C_VERSION, GETOPT_C_SUMMARY);
	for (index = PUTOPTV_I_DETAILS; optv [index] != (char *) (0); index++) 
	{
		fprintf (stderr, " %c%s\n", GETOPT_C_OPTION, optv [index]);
	}
	fprintf (stderr, " %c%c\tversion information\n", GETOPT_C_OPTION, GETOPT_C_VERSION);
	fprintf (stderr, " %c%c\thelp summary\n", GETOPT_C_OPTION, GETOPT_C_SUMMARY);
	fprintf (stderr, "\n");
	fflush (stderr);
	return;
}


#endif

