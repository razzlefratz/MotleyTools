/*====================================================================*
 *
 *   syslog_severity_names.c - syslog priority name table; 
 *
 *   syslogd.h
 *
 *   this vector stores syslog priority names by priority code plus
 *   two additional strings; there SYSLOG_SEVERITIES names plus the
 *   wildcard "*" and NULL list terminator; 
 *
 *   notice that syslog_severity_names[SYSLOG_SEVERITIES] is "*";
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOG_SEVERITY_NAMES_SOURCE
#define SYSLOG_SEVERITY_NAMES_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../linux/syslog.h"
#include "../sysklogd/syslogd.h"

/*====================================================================*
 *   syslog priority names by priority code;
 *--------------------------------------------------------------------*/

char const *syslog_severity_names [SYSLOG_SEVERITIES+2] = 

{
	"emerg",
	"alert",
	"crit",
	"err",
	"warn",
	"notice",
	"info",
	"debug",
	"*",
	(char const *)(0)
};


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

