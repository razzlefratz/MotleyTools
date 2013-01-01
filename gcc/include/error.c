/*====================================================================*
 *
 *   void error (int status, errno_t number, char const *format, ...);
 *
 *   error.h
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ERROR_SOURCE
#define ERROR_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "../tools/types.h"
#include "../tools/error.h"

#ifdef __GNUC__

__attribute__ ((format (printf, 3, 4))) 

#endif

void error (int status, errno_t number, char const *format, ...) 

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
	if (number != (errno_t)(0)) 
	{
		fprintf (stderr, ": %s", strerror (number));
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

