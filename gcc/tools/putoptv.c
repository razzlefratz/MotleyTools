/*====================================================================*
 *
 *   void putoptv (char const * optv [];
 *
 *   putoptv.h
 *
 *   print program information on stdout; informtion is stored as an
 *   ordered string vector; program_name is initialized by function
 *   getoptv; character constants are defined in getoptv.h;
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
	printf ("\n");
	printf (" program: %s\n\n", * optv++);
	printf (" command: %s [options] %s\n\n", program_name, * optv++);
	printf (" options: [%s%c%c]\n\n", * optv++, GETOPTV_C_VERSION, GETOPTV_C_SUMMARY);
	while (* optv)
	{
		printf (" %c%s\n", GETOPTV_C_OPTION, * optv++);
	}
	printf (" %c%c\tversion information\n", GETOPTV_C_OPTION, GETOPTV_C_VERSION);
	printf (" %c%c\thelp summary\n", GETOPTV_C_OPTION, GETOPTV_C_SUMMARY);
	printf ("\n");
	return;
}

#endif



