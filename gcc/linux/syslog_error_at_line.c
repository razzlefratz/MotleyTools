/*====================================================================*
 *
 *   void syslog_error_at_line (int priority, int number, char const *filename, unsigned lineno, char const *format, ...);
 *
 *   syslog.h
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOG_ERROR_AT_LINE_SOURCE
#define SYSLOG_ERROR_AT_LINE_SOURCE

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

#include "../linux/syslog.h"
#include "../tools/sizes.h"

#ifdef __GNUC__

__attribute__ ((format (printf, 5, 6))) 

#endif

void syslog_error_at_line (int priority, errno_t number, char const *filename, size_t lineno, char const *format, ...) 

{
	va_list arglist;
	va_start (arglist, format);
	if (filename != (char const *) (0)) 
	{
		char buffer [strlen (format) + ERRORMSG_MAX];
		snprintf (buffer, sizeof (buffer), "%s(%d): ", filename, lineno);
		vsyslog (priority, buffer, arglist);
	}
	else 
	{
		vsyslog (priority, format, arglist);
	}
	va_end (arglist);
	return;
}


#endif

