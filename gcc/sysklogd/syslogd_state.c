/*====================================================================*
 *
 *   syslogd_state.c -
 *
 *   syslogd.h
 *
 *   print the internal state of a syslogd structure on stdout; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOGD_STATE_SOURCE
#define SYSLOGD_STATE_SOURCE

#include <stdio.h>
#include <time.h>

#include "../sysklogd/syslogd.h"
#include "../strlib/strlib.h"
#include "../tools/flags.h"
#include "../tools/types.h"
#include "../date/date.h"

void syslogd_state (struct syslogd * syslog, flag_t flags, FILE * fp) 

{ 
	extern char const * syslogd_type_names []; 
	extern char const * syslogd_flag_names []; 
	extern char const * syslog_facility_names []; 
	extern char const * syslog_severity_names []; 
	facility_t facility; 
	char buffer [1024]; 

#if SYSLOGD_TRACE

	trace_enter ("syslogd_state"); 

#endif

	fprintf (fp, "type = [%s]\n", syslogd_type_names [syslog->f_type]); 
	fprintf (fp, "name = [%s]\n", syslog->f_name); 
	fprintf (fp, "desc = (%d)\n", syslog->f_desc); 
	strftime (buffer, sizeof (buffer), LOGTIME, localtime (& syslog->f_time)); 
	fprintf (fp, "time = [%s]\n", buffer); 
	strfbits (buffer, sizeof (buffer), syslogd_flag_names, "|", syslog->f_flags); 
	fprintf (fp, "flags = 0x%04X [%s]\n", syslog->f_flags, buffer); 
	for (facility = 0; facility < SYSLOG_FACILITIES; facility++) 
	{ 
		strfbits (buffer, sizeof (buffer), syslog_severity_names, "|", syslog->f_severity [facility]); 
		fprintf (fp, "facility[%02d] = 0x%02X %8s [%s]\n", facility, syslog->f_severity [facility], syslog_facility_names [facility], buffer); 
	} 
	fprintf (fp, "posted = [%s]\n", syslog->f_posted); 

#if SYSLOGD_ORIGIN

	fprintf (fp, "origin = [%s]\n", syslog->f_origin); 

#endif
#if SYSLOGD_NATURE

	fprintf (fp, "nature = [%s]\n", syslog->f_nature); 

#endif

	fprintf (fp, "notice = [%s]\n", syslog->f_notice); 
	fprintf (fp, "length = %d\n", syslog->f_length); 
	fprintf (fp, "repeat = %d\n", syslog->f_repeat); 
	fprintf (fp, "\n"); 

#if SYSLOGD_TRACE

	trace_leave ("syslogd_state"); 

#endif

	return; 
} 

#endif



