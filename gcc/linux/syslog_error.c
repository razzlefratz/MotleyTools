/*====================================================================*
 *
 *   void syslog_error (int priority, errno_t number, char const *format, ...);
 *
 *   syslog.h
 *
 *   print user message and system error message using the syslogd 
 *   priority;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOG_ERROR_SOURCE
#define SYSLOG_ERROR_SOURCE

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

#include "../linux/syslog.h"
#include "../tools/sizes.h"

#ifdef __GNUC__

__attribute__ ((format (printf, 3, 4))) 

#endif

void syslog_error (int priority, errno_t number, char const *format, ...) 

{
	va_list arglist;
	va_start (arglist, format);
	if (number) 
	{
		char buffer [strlen (format) + ERRORMSG_MAX];
		snprintf (buffer, sizeof (buffer), "%s: %s", format, strerror (number));
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

