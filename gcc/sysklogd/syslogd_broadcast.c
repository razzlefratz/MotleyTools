/*====================================================================*
 *
 *   void syslog_broadcast (char const *usernames[], char const *message);
 *
 *   broadcast message in iovec vector[] to user terminals specified 
 *   in the usernames string; 
 *
 *   spawn one child to write to each temminal and continue without
 *   waiting; this simplifes the logic flow and prevents the parent
 *   from being held up waiting for children that timeout; 
 *
 *   the username list is terminated with (char *)(0); 
 * 
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOGD_BROADCAST_SOURCE
#define SYSLOGD_BROADCAST_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <netdb.h>
#include <utmp.h>
#include <paths.h>
#include <error.h>
#include <errno.h>
#include <utmp.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../sysklogd/syslogd.h"
#include "../linux/broadcast.h"
#include "../tools/tools.h"
#include "../tools/types.h"
#include "../tools/sizes.h"
#include "../date/date.h"

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

struct terminal 

{
	struct terminal *next;
	char name [sizeof (_PATH_DEV) + UT_LINESIZE + 1];
}

terminal;
struct terminal *old;
struct terminal *new;

/*====================================================================*
 *
 *   void broadcast_alarm_handler (signo_t number);
 *
 *   get a life! timeout and move on;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static void broadcast_sigalrm (signo_t number) 

{
	error (1, ETIME, "Broadcast to terminal %s timed out", new->name);
	return;
}


/*====================================================================*
 *
 *   void syslogd_broadcast (char const *usernames[], struct iovec message[], size_t elements, flag_t flags);
 *
 *   broadcast struct iovec messages[] to terminals associated with  
 *   the usernames[] string vector; username "*" means everybody; 
 *
 *   spawn one child to write to each temminal and continue without
 *   waiting; this simplifes the logic flow and prevents the parent
 *   from being held up waiting for children that timeout; 
 *
 *   the username list is terminated with (char *)(0); 
 * 
 *--------------------------------------------------------------------*/

void syslogd_broadcast (char const *usernames [], struct iovec message [], size_t elements, flag_t flags) 

{
	extern char const *program_name;
	extern char const *host_name;
	struct utmp *utmp;
	char banner [LINESIZE_MAX];
	char const **username;
	time_t now = time (&now);
	size_t length = 0;

#if SYSLOGD_TRACE

	trace_enter ("syslogd_broadcast");

#endif

	length += snprintf (banner + length, sizeof (banner) - length, "Broadcast ");
	length += snprintf (banner + length, sizeof (banner) - length, USERWHO, program_name, host_name);
	length += strftime (banner + length, sizeof (banner) - length, NOWTIME, localtime (&now));
	new = NEW (struct terminal);
	new->name [0] = (char) (0);
	new->next = new;
	setutent ();
	while ((utmp = getutent ()) != (struct utmp *) (0)) 
	{
		if (utmp->ut_type != USER_PROCESS) 
		{
			continue;
		}
		if (*utmp->ut_name == (char) (0)) 
		{
			continue;
		}
		for (username = usernames; *username != (char const *) (0); username++) 
		{
			if (**username == '*') 
			{
				break;
			}
			if (strncmp (*username, utmp->ut_name, sizeof (utmp->ut_name)) == 0) 
			{
				break;
			}
		}
		if (*username == (char const *) (0)) 
		{
			continue;
		}
		if (strncmp (utmp->ut_line, _PATH_DEV, sizeof (_PATH_DEV))) 
		{
			strncpy (new->name, _PATH_DEV, sizeof (_PATH_DEV));
			strncat (new->name, utmp->ut_line, sizeof (utmp->ut_line));
		}
		else 
		{
			strncpy (new->name, utmp->ut_line, sizeof (utmp->ut_line));
		}
		for (old = new->next; strcmp (old->name, new->name); old = old->next);
		if (old != new) 
		{
			continue;
		}
		if (!fork ()) 
		{
			file_t fd;
			struct sigaction sa;
			memset (&sa, 0, sizeof (sa));
			sa.sa_handler = broadcast_sigalrm;
			sa.sa_flags = 0;
			sigemptyset (&sa.sa_mask);
			sigaction (SIGALRM, &sa, (struct sigaction *) (0));
			alarm (BROADCAST_T_TIMEOUT);
			if ((fd = open (new->name, O_WRONLY | O_NONBLOCK | O_NOCTTY)) != -1) 
			{
				if (isatty (fd)) 
				{

#ifdef NEEDED

					write (fd, "\r\n", 2);
					write (fd, banner, length);
					write (fd, "\r\n", 2);
					writev (fd, message, elements);
					write (fd, "\r\n", 2);
					write (fd, "\a", 1);

#else

					writev (fd, message, elements);

#endif

				}
				close (fd);
			}
			alarm (0);
			exit (0);
		}
		new = NEW (struct terminal);
		new->name [0] = (char) (0);
		new->next = old->next;
		old->next = new;
	}
	endutent ();
	while (new->next != new) 
	{
		old = new->next;
		new->next = old->next;
		old->next = (struct terminal *) (0);
		free (old);
	}
	free (new);

#if SYSLOGD_TRACE

	trace_leave ("syslogd_broadcast");

#endif

	return;
}


#endif

