/*====================================================================*
 *   
 *   void syslogd_index (struct syslogd *syslog, flag_t flags, facility_t facility, severity_t severity);
 *   
 *   struct syslogd contains an array of severity bitmaps, one map  
 *   per facility; this function sets or clears severity bits in one 
 *   or more facility maps; the result can be printed using 
 *   syslogd_enumerate();
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOGD_INDEX_SOURCE
#define SYSLOGD_INDEX_SOURCE

#include "../linux/syslog.h"
#include "../sysklogd/syslogd.h"
#include "../tools/flags.h"

void syslogd_index (struct syslogd *syslog, flag_t flags, facility_t facility, severity_t severity) 

{

#if SYSLOGD_TRACE

	trace_enter ("syslogd_index");

#endif

	if (severity == SYSLOG_SEVERITY_NONE) 
	{
		if (_anyset (syslog->f_flags, SYSLOGD_FLAG_NEGATE_PRIORITY)) 
		{
			_setbits (syslog->f_severity [facility], SYSLOG_SEVERITY_MAP);
		}
		else 
		{
			_clrbits (syslog->f_severity [facility], SYSLOG_SEVERITY_MAP);
		}
	}
	else if (severity == SYSLOG_SEVERITIES) 
	{
		if (_anyset (syslog->f_flags, SYSLOGD_FLAG_NEGATE_PRIORITY)) 
		{
			_clrbits (syslog->f_severity [facility], SYSLOG_SEVERITY_MAP);
		}
		else 
		{
			_setbits (syslog->f_severity [facility], SYSLOG_SEVERITY_MAP);
		}
	}
	else if (_anyset (syslog->f_flags, SYSLOGD_FLAG_SINGLE_PRIORITY)) 
	{
		if (_anyset (syslog->f_flags, SYSLOGD_FLAG_NEGATE_PRIORITY)) 
		{
			_clrbits (syslog->f_severity [facility], (1 << severity));
		}
		else 
		{
			_setbits (syslog->f_severity [facility], (1 << severity));
		}
	}
	else 
	{
		if (_anyset (syslog->f_flags, SYSLOGD_FLAG_NEGATE_PRIORITY)) 
		{
			do 
			{
				_clrbits (syslog->f_severity [facility], (1 << severity));
			}
			while (severity-- > 0);
		}
		else 
		{
			do 
			{
				_setbits (syslog->f_severity [facility], (1 << severity));
			}
			while (severity-- > 0);
		}
	}

#if SYSLOGD_TRACE

	trace_leave ("syslogd_index");

#endif

	return;
}


#endif

