/*====================================================================*
 *
 *   osyslog.cpp - implementation of the osyslog class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oSYSLOG_SOURCE
#define oSYSLOG_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cctype>
#include <cstring>
#include <cstdarg>
#include <iostream>
#include <fstream>
#include <ctime>

#include <netdb.h>
#include <paths.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/file.h>
#include <sys/signal.h>
#include <sys/syslog.h>
#include <sys/uio.h>
#include <sys/wait.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../../gcc/tools/paths.h"
#include "../../gcc/tools/flags.h"

#include "../classes/osyslog.hpp"
#include "../classes/oerror.hpp"

/*====================================================================*
 *   constant definitions;
 *--------------------------------------------------------------------*/

#define SYSLOG_STRERROR_MAX 128

/*====================================================================*
 *   
 *   osyslog & identity (unsigned identity);
 *   
 *   set the ientity string for this instance only if the new string 
 *   differs from the current string;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

osyslog & osyslog::identity (char const * identity)

{
	if (std::strcmp (this->midentity, identity))
	{
		delete [] this->midentity;
		this->midentity = new char [std::strlen (identity) +  1];
		std::strcpy (this->midentity, identity);
	}
	return (* this);
}

/*====================================================================*
 *   
 *   char const * identity() const;
 *   
 *   return the current identity string for this instance;
 *   
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * osyslog::identity () const

{
	return (this->midentity);
}

/*====================================================================*
 *   
 *   osyslog & facility (facility_t facility);
 *   
 *   set the facility code for this instance; facility codes occupy
 *   bits 3 through 9; bits 0 through 2 are automatically cleared;
 *   facility codes defined in syslog.h are shifted to the correct
 *   position;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

osyslog & osyslog::facility (facility_t facility)

{
	this->mfacility = facility & SYSLOG_FACILITY_MASK;
	return (* this);
}

/*====================================================================*
 *   
 *   facility_t facility() const;
 *   
 *   return the facility code for this instance;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

facility_t osyslog::facility () const

{
	return (this->mfacility);
}

/*====================================================================*
 *   
 *   osyslog & options (flag_t options);
 *   
 *   set the option flag for this instance; options are bitmapped and
 *   defined in syslog.h;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

osyslog & osyslog::options (flag_t options)

{
	this->moptions = options;
	return (* this);
}

/*====================================================================*
 *   
 *   flag_t options() const;
 *   
 *   return the option flag for this instance;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

flag_t osyslog::options () const

{
	return (this->moptions);
}

/*====================================================================*
 *
 *   void syslogerr (priority_t priority, errno_t errornum, char const *format, ...);
 *
 *   print user defined and system defined error message using the 
 *   syslogd service;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void osyslog::syslogerr (priority_t priority, errno_t errnum, char const * format, ...)

{
	va_list arglist;
	va_start (arglist, format);
	if (errnum != (errno_t) (0))
	{
		char buffer [strlen (format) +  SYSLOG_STRERROR_MAX];
		std::snprintf (buffer, sizeof (buffer), "%s: %s", format, std::strerror (errnum));
		osyslog::vsyslog (priority, buffer, arglist);
	}
	else 
	{
		osyslog::vsyslog (priority, format, arglist);
	}
	va_end (arglist);
	return;
}

/*====================================================================*
 *
 *   void syslogerr_at_line (priority_t priority, errno_t errornum, char const *filename, unsigned lineno, char const *format, ...);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void osyslog::syslogerr_at_line (priority_t priority, errno_t errornum, char const * filename, size_t lineno, char const * format, ...)

{
	va_list arglist;
	va_start (arglist, format);
	if (filename != (char const *) (0))
	{
		char buffer [strlen (format) +  SYSLOG_STRERROR_MAX];
		std::snprintf (buffer, sizeof (buffer), "%s: (%zu) ", filename, lineno);
		osyslog::vsyslog (priority, buffer, arglist);
	}
	else 
	{
		osyslog::vsyslog (priority, format, arglist);
	}
	va_end (arglist);
	return;
}

/*====================================================================*
 *   
 *   void syslog (priority_t priority, char const *format, ...);
 *   
 *   print user formatted message to appropriate system log files;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void osyslog::syslog (priority_t priority, char const * format, ...)

{
	va_list arglist;
	va_start (arglist, format);
	osyslog::vsyslog (priority, format, arglist);
	va_end (arglist);
	return;
}

/*====================================================================*
 *   
 *   void vsyslog (priority_t priority, char const *format, va_list arglist);
 *   
 *   print user formatted message to approprite system log files;
 *   reject messages having any non-priority and non-facility bits 
 *   set; reject messages suppressed by the severity mask
 *
 *   if no facility is specified then use the default facility;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void osyslog::vsyslog (priority_t priority, char const * format, va_list arglist)

{
	time_t now = time (& now);
	char buffer [SYSLOG_MESSAGE_MAX] = "";
	signed prefix = 0;
	signed length = 0;
	if (priority & ~ (SYSLOG_FACILITY_MASK | SYSLOG_SEVERITY_MASK))
	{
		return;
	}
	if (this->mseverity & (1 << (priority & SYSLOG_SEVERITY_MASK)))
	{
		return;
	}
	if ((priority & SYSLOG_FACILITY_MASK) == 0)
	{
		priority |= this->mfacility;
	}
	length = prefix = snprintf (buffer +  length, sizeof (buffer) - length, "<%d>", priority);
	if (this->midentity != (char *) (0))
	{
		length += snprintf (buffer +  length, sizeof (buffer) - length, "%s: ", this->midentity);
	}
	if (this->moptions & SYSLOG_PROCESS)
	{
		length += snprintf (buffer +  length, sizeof (buffer) - length, "[%d] ", getpid ());
	}
	length += vsnprintf (buffer +  length, sizeof (buffer) - length, format, arglist);
	length += snprintf (buffer +  length, sizeof (buffer) - length, "\n");
	if (this->moptions & SYSLOG_PERROR)
	{
		std::cerr.write (buffer +  prefix, length - prefix);
	}
	if (write (this->mfile, buffer, length) == - 1)
	{
		if (this->moptions & SYSLOG_CONSOLE)
		{
			std::ofstream console;
			console.open (_PATH_CONSOLE, std::ofstream::out);
			if (console.good ())
			{
				console.write (buffer +  prefix, length - prefix);
			}
			console.close ();
		}
	}
	return;
}

/*====================================================================*
 *
 *   osyslog();
 *   
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

osyslog::osyslog ()

{
	this->midentity = new char [L_cuserid];
	std::strncpy (this->midentity, getlogin (), sizeof (this->midentity));
	this->mfacility = SYSLOG_USER;
	this->mseverity = 0;
	this->moptions = 0;
	this->msocket.sa_family = AF_UNIX;
	std::strncpy (this->msocket.sa_data, _PATH_LOG, sizeof (this->msocket.sa_data));
	if ((this->mfile = socket (AF_UNIX, SOCK_DGRAM, 0)) == - 1)
	{
		oerror::error (1, errno, "can't open udp socket");
	}
	if (connect (this->mfile, & this->msocket, sizeof (this->msocket)) == - 1)
	{
		oerror::error (1, errno, "can't connect to %s", this->msocket.sa_data);
	}
	return;
}

/*====================================================================*
 *
 *   ~osyslog();
 *   
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

osyslog::~ osyslog ()

{
	delete [] this->midentity;::
	close (this->mfile);
	return;
}

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif 



