/*====================================================================*
 *
 *   void syslogd_stop (signal_t sig)
 *
 *   print a stop message (as a coutesy to system operators) before 
 *   system logging is stopped; otherise, your message will fall on
 *   deaf ears;
 *
 *   stop system logging by walking the syslogs list, flushing any
 *   duplicate message information, closing syslogs that should be
 *   closed and removing them from the list; 
 *
 *   there should be one syslog left in the syslogs list on exit;
 *
 *   external variable program_name is declared in module getoptv
 *   and initialized there when the command line is parsed; 
 *
 *   do not enable sigterm because we don't want to process multiple 
 *   sigterms while terminating;
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOGD_STOP_SOURCE
#define SYSLOGD_STOP_SOURCE

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

#include "../sysklogd/syslogd.h"
#include "../tools/version.h"
#include "../tools/types.h"

void syslogd_stop (struct syslogd *syslogs, flag_t flags) 

{
	extern char const *program_name;
	struct syslogd *syslog;

#if SYSLOGD_TRACE

	trace_enter ("syslogd_stop");

#endif

	syslogd_print (SYSLOG_SYSLOG|SYSLOG_NOTICE, "%s %s.%s stopped", program_name, VERSION, RELEASE);
	while (syslogs->next != syslogs) 
	{
		syslog = syslogs->next;
		syslog->next->prev = syslogs;
		syslogs->next = syslog->next;
		if (syslog->f_repeat > 0) 
		{
			syslogd_write (syslog, flags);
		}
		if (syslog->f_sockaddr_in != (struct sockaddr_in *)(0)) 
		{
			free (syslog->f_sockaddr_in);
			syslog->f_sockaddr_in = (struct sockaddr_in *)(0);
		}
		switch (syslog->f_type) 
		{
		case SYSLOGD_TYPE_HOST:
		case SYSLOGD_TYPE_FILE:
		case SYSLOGD_TYPE_PIPE:
		case SYSLOGD_TYPE_TERM:
		case SYSLOGD_TYPE_CONSOLE:
			close (syslog->f_desc);
			break;
		}
		syslog->prev = (struct syslogd *) (0);
		syslog->next = (struct syslogd *) (0);
		free (syslog->f_name);
		free (syslog);
	}

#if SYSLOGD_TRACE

	trace_leave ("syslogd_stop");

#endif

	return;
}


#endif

