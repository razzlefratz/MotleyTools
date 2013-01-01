/*====================================================================*
 *   
 *   void syslogd_start (struct syslogd *syslogs, flag_t flags, char const *filename);
 *   
 *   start or restart system logging by reading the configuration
 *   file, creating syslogd structures, opening associated sockets
 *   and files, linking valid structures into a list and unlinking 
 *   superfluous ones; 
 *
 *   the statement() function returns one configuration file line
 *   after removing comments, concatenating continuation text and
 *   condensing blank space;  
 *
 *   syslogd_parse() fills a syslogd structure with instructions
 *   and syslogd_ready() opens the associated log; the main loop
 *   appends valid structures to the list, discards invalid ones 
 *   and removes duplicates;
 *
 *   when removing duplicates, find another syslog with the same 
 *   name and remove it so that new ones replace old ones; never 
 *   remove the default syslog, even when when it is duplicated; 
 *
 *   post the version, release and state information information 
 *   after the syslogs are opened;
 *
 *   external variable program_name is defined in module getoptv
 *   and updated when the command line is first parsed; 
 *
 *   external variable syslogd_state_names is defined in module 
 *   syslogd_state_names;
 *
 *   this function is called by main() and syslogd_sighup(); to
 *   stop logging call syslogd_stop();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOGD_START_SOURCE
#define SYSLOGD_START_SOURCE

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#include "../sysklogd/syslogd.h"
#include "../strlib/strlib.h"
#include "../tools/version.h"
#include "../tools/tools.h"
#include "../tools/flags.h"
#include "../tools/types.h"

void syslogd_start (struct syslogd *syslogs, flag_t flags, char const *filename) 

{
	extern char const *program_name;
	char buffer [TEXTLINE_MAX];
	size_t lineno = 0;
	file_t fd;

#if SYSLOGD_TRACE

	trace_enter ("syslogd_start");

#endif

	if ((fd = open (filename, O_RDONLY)) == -1) 
	{
		syslogd_error (errno, "Can't open %s", filename);
		return;
	}
	while (statement (fd, buffer, sizeof (buffer), &lineno)) 
	{
		struct syslogd *syslog = NEW (struct syslogd);
		memset (syslog, 0, sizeof (struct syslogd));
		syslog->f_type = SYSLOGD_TYPE_NONE;
		syslog->f_name = "";
		syslog->f_line = lineno;
		syslog->f_desc = -1;
		syslog->f_time = time ((time_t *) (0));
		syslogd_parse (syslog, flags, buffer);
		syslogd_ready (syslog, flags);
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
		for (syslog = syslogs->next; syslog != syslogs->prev; syslog = syslog->next) 
		{
			if (!strcmp (syslog->f_name, syslogs->prev->f_name)) 
			{
				syslogd_print (SYSLOG_SYSLOG | SYSLOG_WARNING, "New %s selections on line %d replace old ones on line %d", syslogs->prev->f_name, syslogs->prev->f_line, syslog->f_line);
				syslog->next->prev = syslog->prev;
				syslog->prev->next = syslog->next;
				syslog->prev = (struct syslogd *) (0);
				syslog->next = (struct syslogd *) (0);
				free (syslog->f_name);
				free (syslog);
				break;
			}
		}
	}
	close (fd);
	syslogd_print (SYSLOG_SYSLOG | SYSLOG_NOTICE, "%s %s.%s started", program_name, VERSION, RELEASE);
	syslogd_print (SYSLOG_SYSLOG | SYSLOG_INFO, "Configured with %s", filename);

#if SYSLOGD_TRACE

	trace_leave ("syslogd_start");

#endif

	return;
}


#endif

