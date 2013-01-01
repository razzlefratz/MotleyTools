/*====================================================================*
 *
 *   void event (int status, signo_t number, char const *format, ...);
 *
 *   error.h
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef EVENT_SOURCE
#define EVENT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "../tools/types.h"
#include "../tools/error.h"

#ifdef __GNUC__

__attribute__ ((format (printf, 3, 4))) 

#endif

void event (int status, signo_t number, char const *format, ...) 

{
	extern char const *program_name;
	if (program_name != (char const *) (0)) 
	{
		fprintf (stderr, "%s: ", program_name);
	}
	if (number != (signo_t)(0)) 
	{
		fprintf (stderr, "%s: ", strsignal (number));
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
	if (status != (int)(0)) 
	{
		exit (status);
	}
	return;
}


#endif

