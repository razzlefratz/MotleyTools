/*====================================================================*
 *   
 *   void syslogd_configure (struct syslogd *syslogs, flag_t flags, char const *filename);
 *   
 *   read a syslog configuration file and create one syslog for     
 *   for each statement in that file;
 *
 *   function statement() returns a statement, ignoring comments,
 *   concatenating continuation lines and condensing blank space; it
 *   collects either an empty string or a statement with each call;
 *
 *   syslogd_parse() populates a syslogd with statement information;
 *   valid syslogs are appended to the syslogs list and invalid ones
 *   are discarded; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOGD_CONFIGURE_SOURCE
#define SYSLOGD_CONFIGURE_SOURCE

#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <error.h>
#include <errno.h>

#include "../sysklogd/syslogd.h"
#include "../tools/tools.h"
#include "../tools/types.h"

void syslogd_configure (struct syslogd * syslogs, flag_t flags, char const * filename) 

{ 
	file_t fd; 
	char string [TEXTLINE_MAX]; 
	size_t lineno = 0; 

#if SYSLOGD_TRACE

	trace_enter ("syslogd_configure"); 

#endif

	if ((fd = open (filename, O_RDONLY)) == - 1) 
	{ 
		syslogd_error (errno, "cant open %s", filename); 
		return; 
	} 
	while (statement (fd, string, sizeof (string), & lineno)) 
	{ 
		if (* string != (char) (0)) 
		{ 
			struct syslogd * syslog = NEW (struct syslogd); 
			syslogd_parse (syslog, flags, string); 
			if (syslog->f_type == SYSLOGD_TYPE_NONE) 
			{ 
				free (syslog->f_name); 
				free (syslog); 
				continue; 
			} 
			syslog->prev = syslogs->prev; 
			syslogs->prev->next = syslog; 
			syslogs->prev = syslog; 
			syslog->next = syslogs; 
		} 
	} 
	close (fd); 

#if SYSLOGD_TRACE

	trace_leave ("syslogd_configure"); 

#endif

	return; 
} 

#endif



