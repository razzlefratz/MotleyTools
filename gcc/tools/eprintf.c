/*====================================================================*
 *
 *   void eprintf (char const *format, ...);
 *
 *   local.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef EPRINTF_SOURCE
#define EPRINTF_SOURCE

#include <stdio.h>
#include <stdarg.h>

#include "tools.h"

#ifdef __GNUC__

__attribute__ ((format (printf, 1, 2))) 

#endif

void eprintf (char const *format, ...) 

{
	extern char const *program_name;
	if (program_name != (char const *) (0)) 
	{
		fprintf (stderr, "%s: ", program_name);
	}
	if (format != (char const *) (0)) 
	{
		va_list arglist;
		va_start (arglist, format);
		vfprintf (stderr, format, arglist);
		va_end (arglist);
	}
	fprintf (stderr, "\n");
	fflush (stderr);
	return;
}


#endif

