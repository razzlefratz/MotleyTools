/*====================================================================*
 *
 *   size_t strfpri (char buffer[], size_t length, flag_t option);
 *
 *   syslog.h
 *
 *   encode buffer with the <facility>.<priority> representation of
 *   a syslog option flagword; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRFPRI_SOURCE
#define STRFPRI_SOURCE

#include <stdio.h>
#include <sys/syslog.h>

#include "../linux/syslog.h"
#include "../tools/types.h"
#include "../tools/flags.h"

size_t strfpri (char buffer [], size_t length, flag_t option) 

{
	extern const struct _code_ syslog_facility_codes [];
	extern const struct _code_ syslog_severity_codes [];
	const struct _code_ *facility;
	const struct _code_ *priority;
	for (facility = syslog_facility_codes; facility->name != (char *) (0); facility++) 
	{
		if (facility->code == (option & SYSLOG_FACILITY_MASK)) 
		{
			break;
		}
	}
	for (priority = syslog_severity_codes; priority->name != (char *) (0); priority++) 
	{
		if (priority->code == (option & SYSLOG_SEVERITY_MASK)) 
		{
			break;
		}
	}
	length = snprintf (buffer, length, "%s%c%s", facility->name, SYSLOG_EXTENDER, priority->name);
	return (length);
}


#endif

