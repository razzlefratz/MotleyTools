/*====================================================================*
 *
 *   signed error_on_line (int status, errno_t number, char const *filename, unsigned lineno, char const *format, ...);
 *
 *   error.h
 *
 *   custom implementation of the GNU error_at_line() function for 
 *   environments that do not have it;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ERROR_ON_LINE_SOURCE
#define ERROR_ON_LINE_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "../tools/types.h"
#include "../tools/error.h"

#ifdef __GNUC__

__attribute__ ((format(printf, 5, 6))) 

#endif

signed error_on_line(int status, errno_t number, char const * filename, unsigned lineno, char const * format, ...)

{
	extern char const * program_name;
	if ((program_name) && (* program_name))
	{
		fprintf (stderr, "%s: ", program_name);
	}
	if ((filename) && (* filename))
	{
		fprintf (stderr, "%s (%d): ", filename, lineno);
	}
	if (number)
	{
		fprintf (stderr, "%s: ", strerror(number));
	}
	if ((format) && (* format))
	{
		va_list arglist;
		va_start (arglist, format);
		vfprintf (stderr, format, arglist);
		va_end (arglist);
	}
	fprintf (stderr, "\n");
	fflush (stderr);
	if (status)
	{
		exit (status);
	}
	return (- 1);
}

#endif



