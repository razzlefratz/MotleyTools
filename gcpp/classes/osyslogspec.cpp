/*====================================================================*
 *
 *   osyslogspec.cpp - implementation of the osyslogspec class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oSYSLOGSPEC_SOURCE
#define oSYSLOGSPEC_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdio>
#include <cctype>
#include <cstdarg>
#include <cstring>
#include <ctime>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../../gcc/tools/paths.h"
#include "../../gcc/tools/flags.h"

#include "../classes/osyslog.hpp"
#include "../classes/osyslogspec.hpp"

/*====================================================================*
 *   variable definitions;
 *--------------------------------------------------------------------*/

const struct _code_ osyslogspec::facilities [] = 

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
		(- 1),
		(char const *) (0)
	}
};

const struct _code_ osyslogspec::severities [] = 

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
		INTERNAL_NOPRI,
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
		TABLE_ALLPRI,
		"*"
	},
	{
		(- 1),
		(char const *) (0),
	}
};

/*====================================================================*
 *
 *   int osyslogspec::encode (char const *string);
 *
 *   convert string in form <facility>.<severity> to syslog flagword
 *   format where the lower bits are the severity and the upper bits 
 *   are the facility;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

int osyslogspec::encode (char const * string) const

{
	facility_t facility;
	severity_t severity;
	char buffer [SYSLOG_FACILITY_MAX];
	char * sp;
	for (sp = buffer; * string != (char) (0); string++)
	{
		if (* string == SYSLOG_EXTENDER)
		{
			string++;
			break;
		}
		if ((sp - buffer) < (int) (sizeof (buffer) - 1))
		{
			* sp++ = * string;
		}
	}
	* sp = (char) (0);
	if ((facility = lookup (buffer, osyslogspec::facilities)) == (facility_t) (- 1))
	{
		oerror::error (1, 0, "%s: illegal facility name", buffer);
	}
	if ((severity = lookup (string, osyslogspec::severities)) == (severity_t) (- 1))
	{
		oerror::error (1, 0, "%s: illegal severity name", string);
	}
	return (facility | severity);
}

/*====================================================================*
 *
 *   char *osyslogspec::decode(int flagword) const
 *
 *   convert flagword to user friendly decimal <facility>.<severity> 
 *   string format;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * osyslogspec::decode (int flagword) const

{
	const struct _code_ * facility;
	const struct _code_ * severity;
	static char buffer [SYSLOG_FACILITY_MAX +  SYSLOG_SEVERITY_MAX];
	for (facility = osyslogspec::facilities; facility->name != (char *) (0); facility++)
	{
		if (facility->code & flagword)
		{
			break;
		}
	}
	for (severity = osyslogspec::severities; severity->name != (char *) (0); severity++)
	{
		if (severity->code & flagword)
		{
			break;
		}
	}
	std::snprintf (buffer, sizeof (buffer), "[%s.%s][%04X]", facility->name, severity->name, flagword);
	return (buffer);
}

/*====================================================================*
 *
 *   int lookup (char const *string, const struct _code_ table[]);
 *
 *   convert string to an integer; if string is numeric then attempt 
 *   integer conversion; failing that attempt table lookup; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

int osyslogspec::lookup (char const * string, const struct _code_ table []) const

{
	const struct _code_ * index;
	char const * sp;
	int code = 0;
	for (sp = string; isdigit (* sp); code = (code * 10) +  (* sp++ - '0'));
	if (* sp == (char) (0))
	{
		return (code);
	}
	for (index = table; index->name != (char const *) (0); index++)
	{
		if (strcmp (string, index->name) == 0)
		{
			return (index->code);
		}
	}
	return (0);
}

/*====================================================================*
 *   
 *   osyslogspec();
 *   
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

osyslogspec::osyslogspec ()

{
	return;
}

/*====================================================================*
 *   
 *   ~osyslogspec();
 *   
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

osyslogspec::~ osyslogspec ()

{
	return;
}

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif



