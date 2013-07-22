/*====================================================================*
 *
 *   void syslogd_queue (priority_t priority, char const *origin, char const *notice);
 *
 *   wite notice to appropriate syslogs based on caller dispatch and 
 *   configured syslog types, flags and facility priority masks; 
 *
 *   suppress duplicate notices and replace them with one summary  
 *   notice before outputiing new ones;
 *   
 *   if this message is the same as the last message then count it 
 *   but do not post it; once a different message arrives, post a 
 *   message stating how many times the message was received; 
 *
 *   if this message differs from the last message and the last one  
 *   was repeated then post a message to that effect before writing  
 *   this one; use an empty notice ("") to post the summary message
 *   and reset the counter; 
 *
 *   syslog structures are stored as a circular linked list having 
 *   as least one member; that member is the default log, normally
 *   the console; when all else fails, write to that one; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOGD_QUEUE_SOURCE
#define SYSLOGD_QUEUE_SOURCE

/*--------------------------------------------------------------------*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <time.h>

/*--------------------------------------------------------------------*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../linux/syslog.h"
#include "../sysklogd/syslogd.h"
#include "../strlib/strlib.h"
#include "../tools/types.h"
#include "../tools/flags.h"
#include "../date/date.h"

/*--------------------------------------------------------------------*
 *
 *--------------------------------------------------------------------*/

void syslogd_queue (int priority, char const * origin, char const * notice) 

{ 
	extern flag_t state; 
	extern struct syslogd syslogs; 
	struct syslogd * syslog; 
	facility_t facility = SYSLOG_FACILITY (priority); 
	severity_t severity = SYSLOG_SEVERITY (priority); 
	time_t now = time (& now); 

#if SYSLOGD_TRACE

	trace_enter ("syslogd_queue"); 

#endif

#if SYSLOGD_ORIGIN

	if (origin == (char const *) (0)) 
	{ 
		origin = ""; 
	} 

#endif

	if (notice == (char const *) (0)) 
	{ 
		notice = ""; 
	} 
	for (syslog = syslogs.next; syslog != & syslogs; syslog = syslog->next) 
	{ 
		if (_anyset (syslog->f_flags, SYSLOGD_FLAG_DISABLED)) 
		{ 
			continue; 
		} 
		if (_allclr (syslog->f_severity [facility], (1 << severity))) 
		{ 
			continue; 
		} 
		if (syslog->f_time > now) 
		{ 
			continue; 
		} 
		if (!syslog->f_retry) 
		{ 
			strftime (syslog->f_posted, sizeof (syslog->f_posted), LOGTIME, localtime (& now)); 
		} 

#if SYSLOGD_ORIGIN

		if (!strcmp (notice, syslog->f_notice) && !strcmp (origin, syslog->f_origin)) 

#else

		if (!strcmp (notice, syslog->f_notice)) 

#endif

		{ 
			syslog->f_repeat++; 
			continue; 
		} 
		if (syslog->f_repeat > 0) 
		{ 
			syslog->f_length = snprintf (syslog->f_notice, sizeof (syslog->f_notice), "Previous message received %d times", syslog->f_repeat + 1); 
			syslog->f_repeat = 0; 
			syslogd_write (syslog, state); 
		} 
		if (* notice != (char) (0)) 
		{ 
			syslog->f_priority = priority; 

#if SYSLOGD_ORIGIN

			strncpy (syslog->f_origin, origin, sizeof (syslog->f_origin)); 

#endif
#if SYSLOGD_NATURE

			strfpri (syslog->f_nature, sizeof (syslog->f_nature), priority); 

#endif

			strncpy (syslog->f_notice, notice, sizeof (syslog->f_notice)); 
			syslog->f_repeat = 0; 
			syslogd_ready (syslog, state); 
			syslogd_write (syslog, state); 
		} 
	} 

/*--------------------------------------------------------------------*
 * this loop executes only if the list has one member; in that case
 * the previous loop will not execute and vice verse; messages are
 * unconditionally written to this syslog because there is no other
 * place to post messages;
 *--------------------------------------------------------------------*/

	if (syslog->next == syslog) 
	{ 
		if ((syslog->f_desc = open (syslog->f_name, O_WRONLY | O_NOCTTY)) != - 1) 
		{ 
			syslogd_write (syslog, state); 
			close (syslog->f_desc); 
			syslog->f_desc = - 1; 
		} 
	} 

#if SYSLOGD_TRACE

	trace_leave ("syslogd_queue"); 

#endif

	return; 
} 

#endif



