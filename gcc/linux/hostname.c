/*====================================================================*
 *
 *   char const * hostname ();
 *   
 *   return a pointer to the hostname string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef HOSTNAME_SOURCE
#define HOSTNAME_SOURCE

#include <unistd.h>

#include "../linux/linux.h"
#include "../tools/sizes.h"

char const * hostname () 

{
	static char buffer [HOSTNAME_MAX];
	gethostname (buffer, sizeof (buffer));
	return (buffer);
}


#endif

