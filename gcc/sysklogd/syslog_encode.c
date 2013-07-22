/*====================================================================*
 *
 *   int syslog_encode (char const *string);
 *
 *   syslog.h
 *
 *   convert a string of form <facility>.<severity> to an equivalent
 *   syslog option word where the lower bits are the severity and the 
 *   upper bits are the facility;
 *
 *   [00000000000000000000000][000]
 *
 *   the <facility> prefix is copied to 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOG_ENCODE_SOURCE
#define SYSLOG_ENCODE_SOURCE

#include <string.h>

#include "../tools/types.h"
#include "../tools/error.h"
#include "../linux/syslog.h"

int syslog_encode (char const * string) 

{ 
	extern const struct _code_ syslog_facility_codes []; 
	extern const struct _code_ syslog_severity_codes []; 
	char buffer [SYSLOG_FACILITY_MAX]; 
	char * sp; 
	facility_t facility; 
	severity_t severity; 
	for (sp = buffer; * string != (char) (0); string++) 
	{ 
		if (* string == SYSLOG_EXTENDER) 
		{ 
			string++; 
			break; 
		} 
		if ((sp - buffer) < (sizeof (buffer) - 1)) 
		{ 
			* sp++ = * string; 
		} 
	} 
	* sp = (char) (0); 
	if ((facility = syslog_lookup (buffer, syslog_facility_codes)) == (facility_t) (- 1)) 
	{ 
		error (1, 0, "%s: bad facility name", buffer); 
	} 
	if ((severity = syslog_lookup (string, syslog_severity_codes)) == (severity_t) (- 1)) 
	{ 
		error (1, 0, "%s: bad severity name", string); 
	} 
	return (facility | severity); 
} 

#endif



