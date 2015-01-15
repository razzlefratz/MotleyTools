/*====================================================================*
 *
 *   syslog.c - syslog application function;
 *
 *
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOG_BASIC_SOURCE
#define SYSLOG_BASIC_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <time.h>
#include <paths.h>
#include <errno.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/signal.h>
#include <sys/syslog.h>
#include <sys/uio.h>
#include <sys/wait.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../linux/syslog.h"
#include "../tools/paths.h"
#include "../tools/sizes.h"
#include "../tools/types.h"
#include "../tools/flags.h"

/*====================================================================*
 * program variables;
 *--------------------------------------------------------------------*/

static struct syslog 

{
	char const *identity;
	facility_t facility;
	flag_t severity;
	flag_t options;
	file_t desc;
	struct sockaddr socket;
	bool connected;
}

log = 

{
	SYSLOG_SERVICE_NAME,
	SYSLOG_USER,
	(flag_t)(0),
	(flag_t)(0),
	(file_t)(-1),
	{
		sizeof (struct sockaddr),
		{
			AF_UNIX
		},
		_PATH_LOG
	},
	false
};


/*====================================================================*
 *   
 *   void openlog (char const *identity, int options, int facility);
 *
 *   syslog.h
 *   
 *   open system log with the given identity, facility and options;
 *   identity will start each syslog message; facility will be used
 *   when no facility is specified at print time; options determine
 *   print behavior;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void openlog (char const *identity, int options, int facility) 

{
	if ((identity == (char *) (0)) || (* identity == (char)(0))) 
	{
		identity = getlogin ();
	}
	if (facility & ~(SYSLOG_FACILITY_MASK | SYSLOG_SEVERITY_MASK)) 
	{
		facility = SYSLOG_SYSLOG;
	}
	log.identity = identity;
	log.facility = facility & SYSLOG_FACILITY_MASK;
	log.options = options;
	if (log.desc == -1) 
	{
		if (log.options & SYSLOG_NDELAY) 
		{
			log.desc = socket (AF_UNIX, SOCK_DGRAM, 0);
			if (log.desc == -1) 
			{
				return;
			}
		}
	}
	if (!log.connected) 
	{
		if (connect (log.desc, &log.socket, sizeof (log.socket)) != -1) 
		{
			log.connected = true;
		}
	}
	return;
}


/*====================================================================*
 *   
 *   void vsyslog (int priority, char const *format, va_list arglist);
 *   
 *   syslog.h
 *   
 *   print user formatted message to approprite system log files;
 *   reject messages with no priority or with any non-priority or
 *   non-facility bits set;
 *   
 *   ignore message if bits other than facility and severity bits 
 *   are set; ignore message if corresponding severity bit is not 
 *   set in the mask; use default facility when none is specified;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void vsyslog (int priority, char const *format, va_list arglist) 

{
	char buffer [TEXTLINE_MAX];
	time_t now = time (&now);
	ssize_t prefix = 0;
	ssize_t length = 0;
	if (priority & ~(SYSLOG_FACILITY_MASK | SYSLOG_SEVERITY_MASK)) 
	{
		return;
	}
	if (log.severity & (1 << (priority & SYSLOG_SEVERITY_MASK))) 
	{
		return;
	}
	if ((priority & SYSLOG_FACILITY_MASK) == 0) 
	{
		priority |= log.facility;
	}
	length = prefix = snprintf (buffer + length, sizeof (buffer) - length, "<%d>", priority);
	if ((log.identity != (char *) (0)) && (*log.identity != (char)(0))) 
	{
		length += snprintf (buffer + length, sizeof (buffer) - length, "%s: ", log.identity);
	}
	if (log.options & SYSLOG_PROCESS) 
	{
		length += snprintf (buffer + length, sizeof (buffer) - length, "[%d] ", getpid ());
	}
	length += vsnprintf (buffer + length, sizeof (buffer) - length, format, arglist);
	length += snprintf (buffer + length, sizeof (buffer) - length, "\n");
	if ((log.desc == -1) || (!log.connected)) 
	{
		openlog (log.identity, log.options | SYSLOG_NDELAY, log.severity);
	}
	if (log.options & SYSLOG_PERROR) 
	{
		write (STDERR_FILENO, buffer + prefix, length - prefix);
	}
	if (write (log.desc, buffer, length) < length) 
	{
		if (log.options & SYSLOG_CONSOLE) 
		{
			file_t fd;
			if ((fd = open (_PATH_CONSOLE, O_WRONLY | O_NOCTTY, 0)) != -1) 
			{
				write (fd, buffer + prefix, length - prefix);
				close (fd);
			}
		}
	}
	return;
}


/*====================================================================*
 *   
 *   void syslog (int priority, char const *format, ...);
 *   
 *   syslog.h
 *   
 *   print user formatted message to appropriate system log files;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifdef __GNUC__

__attribute__ ((format (printf, 2, 3))) 

#endif

void syslog (int priority, char const *format, ...) 

{
	va_list arglist;
	va_start (arglist, format);
	vsyslog (priority, format, arglist);
	va_end (arglist);
	return;
}


/*====================================================================*
 *   
 *   void closelog ();
 *   
 *   syslog.h
 *   
 *   close the system log;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void closelog () 

{
	log.connected = false;
	log.desc = -1;
	return;
}


/*====================================================================*
 *   
 *   int setlogmask (int severity);
 *   
 *   syslog.h
 *   
 *   set severity mask to severity if the severity argument is not 0; 
 *   return previous severity mask value; 
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

int setlogmask (int severity) 

{
	int previous = log.severity;
	if (severity != 0) 
	{
		log.severity = severity;
	}
	return (previous);
}


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

