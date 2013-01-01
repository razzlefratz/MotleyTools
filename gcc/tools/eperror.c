/*====================================================================*
 *
 *   void eperror (char const *format, ...);
 *
 *   local.h
 *
 *   print error messages using a variable argument list; prefix
 *   messages with prog.name; suffix messages with the text from 
 *   strerror(errno);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef EPERROR_SOURCE
#define EPERROR_SOURCE

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

#include "tools.h"

#ifdef __GNUC__

__attribute__ ((format (printf, 1, 2))) 

#endif

void eperror (char const *format, ...) 

{
	extern char const *program_name;
	if ((program_name) && (*program_name)) 
	{
		fprintf (stderr, "%s: ", program_name);
	}
	if ((format) && (*format)) 
	{
		va_list arglist;
		va_start (arglist, format);
		vfprintf (stderr, format, arglist);
		va_end (arglist);
	}
	if (errno) 
	{
		fprintf (stderr, ": %s", strerror (errno));
	}
	fprintf (stderr, "\n");
	fflush (stderr);
	return;
}


#endif

