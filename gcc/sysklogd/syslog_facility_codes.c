/*====================================================================*
 *
 *   syslog_facility_codes.c - facility code by facility name table; 
 *
 *   this is the code facilities[] in sys/syslog.h with the
 *   addition of the "*" entry; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOG_FACILITY_CODE_HEADER
#define SYSLOG_FACILITY_CODE_HEADER

#include "../linux/syslog.h"
#include "../tools/types.h"

const struct _code_ syslog_facility_codes [] = 

{
	{
		SYSLOG_AUTH,
		"auth"
	},
	{
		SYSLOG_AUTHPRIV,
		"authpriv"
	},
	{
		SYSLOG_CRON,
		"cron"
	},
	{
		SYSLOG_DAEMON,
		"daemon"
	},
	{
		SYSLOG_KERN,
		"kern"
	},
	{
		SYSLOG_LPR,
		"lpr"
	},
	{
		SYSLOG_MAIL,
		"mail"
	},
	{
		SYSLOG_MARK,
		"mark"
	},
	{
		SYSLOG_NEWS,
		"news"
	},
	{
		SYSLOG_AUTH,
		"security"
	},
	{
		SYSLOG_SYSLOG,
		"syslog"
	},
	{
		SYSLOG_USER,
		"user"
	},
	{
		SYSLOG_UUCP,
		"uucp"
	},
	{
		SYSLOG_FTP,
		"ftp"
	},
	{
		SYSLOG_LOCAL0,
		"local0"
	},
	{
		SYSLOG_LOCAL1,
		"local1"
	},
	{
		SYSLOG_LOCAL2,
		"local2"
	},
	{
		SYSLOG_LOCAL3,
		"local3"
	},
	{
		SYSLOG_LOCAL4,
		"local4"
	},
	{
		SYSLOG_LOCAL5,
		"local5"
	},
	{
		SYSLOG_LOCAL6,
		"local6"
	},
	{
		SYSLOG_LOCAL7,
		"local7"
	},
	{
		SYSLOG_FACILITIES,
		"*"
	},
	{
		(signed)(-1),
		(char const *) (0)
	},
};


#endif

