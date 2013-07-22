/*====================================================================*
 *   
 *   void syslogd_admin (struct syslogd *syslogs, flag_t flags, char const *filename);
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOGD_ADMIN_SOURCE
#define SYSLOGD_ADMIN_SOURCE

#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <error.h>
#include <errno.h>

#include "../sysklogd/syslogd.h"
#include "../strlib/strlib.h"
#include "../tools/version.h"
#include "../tools/tools.h"
#include "../tools/types.h"

#ifdef SYSLOGD_REPORT

void syslogd_admin (struct syslogd * syslogs, flag_t flags, char const * filename) 

{ 
	FILE * fp; 
	struct syslogd * syslog; 

#if SYSLOGD_TRACE

	trace_enter ("syslogd_admin"); 

#endif

	if ((filename == (char *) (0)) || (* filename == (char) (0))) 
	{ 
		return; 
	} 
	if ((fp = fopen (filename, "w")) == (FILE *) (0)) 
	{ 
		syslogd_error (errno, "can't open %s", filename); 
		return; 
	} 
	syslogd_enumerate (syslogs, flags, fp); 
	for (syslog = syslogs->next; syslog != syslogs; syslog = syslog->next) 
	{ 
		syslogd_state (syslog, flags, fp); 
	} 
	syslogd_state (syslog, flags, fp); 
	fclose (fp); 

#if SYSLOGD_TRACE

	trace_leave ("syslogd_admin"); 

#endif

	return; 
} 

#endif
#endif



