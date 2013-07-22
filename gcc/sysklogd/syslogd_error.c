/*====================================================================*
 *
 *   void syslogd_error (errno_t number, char const *format, ...);
 *
 *   emulate the GNU error() function call without the exit status
 *   option; if the error number is 0 then behave like printf() but
 *   post to the system logs instead of stdout; otherwise, include 
 *   the system message text from strerror() with the message;
 *
 *   the general form of an error message is:
 *
 *   <date> <time> <host> <name>: <message>[: <error>]
 *
 *   the "no error message" string is posted only if program_name 
 *   is null, format is null and number is 0; 
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOGD_ERROR_SOURCE
#define SYSLOGD_ERROR_SOURCE

#include <unistd.h>
#include <stdarg.h>
#include <string.h>

#include "../sysklogd/syslogd.h"
#include "../tools/types.h"

#ifdef __GNUC__

__attribute__ ((format (printf, 2, 3))) 

#endif

void syslogd_error (errno_t number, char const * format, ...) 

{ 
	extern char const * host_name; 
	extern char const * program_name; 
	char buffer [TEXTLINE_MAX] = "no error message"; 
	size_t length = 0; 

#if SYSLOGD_TRACE

	trace_enter ("syslogd_error"); 

#endif

	if ((program_name != (char const *) (0)) && (* program_name != (char) (0))) 
	{ 
		length += snprintf (buffer + length, sizeof (buffer) - length, "%s: ", program_name); 
	} 
	if ((format != (char const *) (0)) && (* format != (char) (0))) 
	{ 
		va_list arglist; 
		va_start (arglist, format); 
		length += vsnprintf (buffer + length, sizeof (buffer) - length, format, arglist); 
		va_end (arglist); 
	} 
	if (number != (errno_t) (0)) 
	{ 
		length += snprintf (buffer + length, sizeof (buffer) - length, ": %s", strerror (number)); 
	} 
	syslogd_queue (SYSLOG_SYSLOG | SYSLOG_ERR, host_name, buffer); 

#if SYSLOGD_TRACE

	trace_leave ("syslogd_error"); 

#endif

	return; 
} 

#endif



