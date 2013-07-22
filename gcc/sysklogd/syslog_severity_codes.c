/*====================================================================*
 *
 *   syslog_severity_codes.c - priority code by priority name table; 
 *
 *   this is the code prioritynames[] from sys/syslog.h with 
 *   the addition of the "*" entry; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOG_SEVERITY_CODE_HEADER
#define SYSLOG_SEVERITY_CODE_HEADER

#include "../tools/types.h"
#include "../linux/syslog.h"

const struct _code_ syslog_severity_codes [] = 

{ 
	{ 
		SYSLOG_ALERT, 
		"alert"
	}, 
	{ 
		SYSLOG_CRIT, 
		"crit"
	}, 
	{ 
		SYSLOG_DEBUG, 
		"debug"
	}, 
	{ 
		SYSLOG_EMERG, 
		"emerg"
	}, 
	{ 
		SYSLOG_ERR, 
		"err"
	}, 
	{ 
		SYSLOG_ERR, 
		"error"
	}, 
	{ 
		SYSLOG_INFO, 
		"info"
	}, 
	{ 
		SYSLOG_SEVERITY_NONE, 
		"none"
	}, 
	{ 
		SYSLOG_NOTICE, 
		"notice"
	}, 
	{ 
		SYSLOG_EMERG, 
		"panic"
	}, 
	{ 
		SYSLOG_WARNING, 
		"warn"
	}, 
	{ 
		SYSLOG_WARNING, 
		"warning"
	}, 
	{ 
		SYSLOG_SEVERITIES, 
		"*"
	}, 
	{ 
		(signed) (- 1), 
		(char const *) (0)
	} 
}; 

#endif



