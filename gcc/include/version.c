/*====================================================================*
 *
 *   void version();
 *
 *   version.h
 *
 *   print program and package version information on stderr; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef VERSION_SOURCE
#define VERSION_SOURCE

#include <stdio.h>
#include <stdlib.h>

#include "../tools/version.h"

void version () 

{
	extern char const *program_name;
	fprintf (stderr, "%s ", program_name);
	fprintf (stderr, PACKAGE "-");
	fprintf (stderr, VERSION ".");
	fprintf (stderr, RELEASE " ");
	fprintf (stderr, CONTACT " ");
	fprintf (stderr, COMPILE "\n");
	return;
}


#endif

