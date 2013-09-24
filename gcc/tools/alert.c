/*====================================================================*
 *
 *   signed alert (char const *format, ...);
 *
 *   error.h
 *
 *   alternative to the GNU error() function that has no exitcode  
 *   or errno argument and always returns to the calling function;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ALERT_SOURCE
#define ALERT_SOURCE

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "../tools/error.h"

#ifdef __GNUC__

__attribute__ ((format(printf, 1, 2))) 

#endif

signed alert(char const * format, ...)

{
	extern char const * program_name;
	if ((program_name) && (* program_name))
	{
		fprintf (stderr, "%s: ", program_name);
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
	return (- 1);
}

#endif



