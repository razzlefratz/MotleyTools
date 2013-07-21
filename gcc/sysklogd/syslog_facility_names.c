/*====================================================================*
 *
 *   syslog_facility_names.c - syslog facility name table;
 *
 *   syslogd.h
 *
 *   this vector stores syslog facility names by facility code plus
 *   two additional strings; there SYSLOG_FACILITIES names plus the
 *   wildcard "*" and NULL list terminator; 
 *
 *   notice that syslog_facility_names[SYSLOG_FACILITIES] is "*";
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOG_FACILITY_NAMES_SOURCE
#define SYSLOG_FACILITY_NAMES_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../linux/syslog.h"
#include "../sysklogd/syslogd.h"

/*====================================================================*
 *  syslog facility name by facility code; 
 *--------------------------------------------------------------------*/

char const * syslog_facility_names [SYSLOG_FACILITIES +2] = 

{ 
	"kern", 
	"user", 
	"mail", 
	"daemon", 
	"auth", 
	"syslog", 
	"lpr", 
	"news", 
	"uucp", 
	"cron", 
	"authpriv", 
	"ftp", 
	"(n/a)", 
	"(n/a)", 
	"(n/a)", 
	"(n/a)", 
	"local0", 
	"local1", 
	"local2", 
	"local3", 
	"local4", 
	"local5", 
	"local6", 
	"local7", 
	"mark", 
	"*", 
	(char const *) (0)
}; 

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#endif



