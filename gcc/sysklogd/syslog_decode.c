/*====================================================================*
 *
 *   char *syslog_decode (int priority);
 *
 *   syslog.h
 *
 *   convert syslog option flagword to <facility>.<severity> string 
 *   format; the resulting string is stored internally and replaced
 *   after each call; however, option -1 returns the last string; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOG_OPTION_DECODE_SOURCE
#define SYSLOG_OPTION_DECODE_SOURCE

#include <stdio.h>
#include <sys/syslog.h>

#include "../linux/syslog.h"
#include "../tools/types.h"
#include "../tools/flags.h"

char const *syslog_decode (int priority) 

{
	extern const struct _code_ syslog_facility_codes [];
	extern const struct _code_ syslog_severity_codes [];
	const struct _code_ *facility;
	const struct _code_ *severity;
	static char buffer [SYSLOG_SEVERITY_MAX] = "";
	if (priority == -1) 
	{
		return (buffer);
	}
	for (facility = syslog_facility_codes; facility->name != (char *) (0); facility++) 
	{
		if (facility->code == (priority & SYSLOG_FACILITY_MASK)) 
		{
			break;
		}
	}
	for (severity = syslog_severity_codes; severity->name != (char *) (0); severity++) 
	{
		if (severity->code == (priority & SYSLOG_SEVERITY_MASK)) 
		{
			break;
		}
	}
	snprintf (buffer, sizeof (buffer), "%s%c%s", facility->name, SYSLOG_EXTENDER, severity->name);
	return (buffer);
}


#endif

