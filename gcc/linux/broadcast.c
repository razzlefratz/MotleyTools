/*====================================================================*
 *
 *   broadcast.c 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef BROADCAST_SOURCE
#define BROADCAST_SOURCE

/*====================================================================*
 *   system header files; 
 *--------------------------------------------------------------------*/

#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <syslog.h>
#include <time.h>
#include <utmp.h>
#include <fcntl.h>
#include <errno.h>
#include <paths.h>

/*====================================================================*
 *   custom header files; 
 *--------------------------------------------------------------------*/

#include "../linux/broadcast.h"
#include "../tools/memory.h"
#include "../tools/tools.h"
#include "../tools/types.h"
#include "../tools/sizes.h"
#include "../tools/error.h"
#include "../date/date.h"

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

struct terminal 

{
	struct terminal *next;
	char name [sizeof (_PATH_DEV) + UT_LINESIZE + 1];
}

*new,
*old;

/*====================================================================*
 *
 *   signed likeatty (char const *fname);
 *
 *   check whether given filename looks like tty device.
 *
 *   It would be an impossible task to list all major/minors of tty 
 *   devices here, so we just exclude the obvious majors of which 
 *   just opening has side-effects, like printers and tapes;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static signed likeatty (char const *filename) 

{
	struct stat statinfo;
	if (stat (filename, &statinfo) == -1) 
	{
		return (0);
	}
	if (statinfo.st_nlink != 1) 
	{
		if (!S_ISCHR (statinfo.st_mode)) 
		{
			return (0);
		}
	}
	switch (major (statinfo.st_dev)) 
	{
	case 1:
	case 2:
	case 6:
	case 9:
	case 12:
	case 16:
	case 21:
	case 27:
	case 37:
	case 96:
	case 97:
	case 206:
	case 230:
		return (0);
		break;
	default:
		break;
	}
	return (1);
}


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

static void broadcast_alarm_handler (signo_t number) 

{
	error (1, ETIME, "Broadcast to terminal %s timed out", new->name);
	return;
}


/*====================================================================*
 *
 *   int broadcast (char const *string, flag_t flags);
 *
 *   broadcast string and optional banner to active user terminals;
 *
 *   file _PATH_UTMP is searched for login sessions having terminals;
 *   users can open more than one terminal or share terminals causing
 *   multiple broadcasts and so we ignore duplicate terminal entries; 
 *
 *   new terminals are appended to the terminal[] list; the list is
 *   searched for a match; if one exists the new terminal is ignored; 
 *   otherwise, we broadcast there and increment the list count;
 *  
 *   child processes are spawned to broadcast on each terminal; the
 *   parent does not wait for completion or check exit status; child 
 *   processes may fail or timeout without affecting the parent;
 *
 *   BROADCAST_B_REMOTE disables broadcast on the originating terminal; 
 *
 *   BROADCAST_B_BANNER shows the originator and the broadcast time;
 *   non-root users cannot suppress the banner; this discourages any 
 *   phantom broadcasts; 
 *
 *   BROADCAST_B_RECEIPT lists (on stderr) terminals that received
 *   the broadcast as broadcasting progresses; 
 *
 *   BROADCAST_B_SUMMARY lists (on stderr) the number of terminals  
 *   that received the broadcast once broadcasting completes;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed broadcast (char const *string, flag_t flags) 

{
	struct stat statinfo;
	struct utmp *utmp;
	char banner [LINESIZE_MAX] = "";
	size_t length = 0;
	int count = 0;
	if (stat (_PATH_UTMP, &statinfo)) 
	{
		error (1, errno, "can't stat %s", _PATH_UTMP);
	}
	if ((flags & BROADCAST_B_BANNER) || getuid ()) 
	{
		time_t now = time (&now);
		char hostname [HOSTNAME_MAX] = "";
		gethostname (hostname, sizeof (hostname));
		length += snprintf (banner + length, sizeof (banner) - length, "Broadcast");
		length += snprintf (banner + length, sizeof (banner) - length, USERWHO, getlogin (), hostname);
		length += strftime (banner + length, sizeof (banner) - length, NOWTIME, localtime (&now));
		length += snprintf (banner + length, sizeof (banner) - length, "\r\n\r\n");
	}
	new = NEW (struct terminal);
	new->name [0] = (char) (0);
	new->next = new;
	setutent ();
	while ((utmp = getutent ()) != (struct utmp *) (0)) 
	{

/*
 * skip non-user-process entries, entries with empty usernames and entries
 * with PIDs that are no longer running; if things work then the last case
 * should not occur but it does;
 */

		if (utmp->ut_type != USER_PROCESS) 
		{
			continue;
		}
		if (utmp->ut_user [0] == (char) (0)) 
		{
			continue;
		}
		if (kill (utmp->ut_pid, 0)) 
		{
			continue;
		}

/*
 * found an acceptable entry; save the device path to avoid 
 * broadcasting to this device more than once;
 */

		if (strncmp (utmp->ut_line, _PATH_DEV, sizeof (_PATH_DEV))) 
		{
			strncpy (new->name, _PATH_DEV, sizeof (_PATH_DEV));
			strncat (new->name, utmp->ut_line, sizeof (utmp->ut_line));
		}
		else 
		{
			strncpy (new->name, utmp->ut_line, sizeof (utmp->ut_line));
		}

/*
 * if the device path is that of stdin and the caller elected not
 * to broadcast on the local terminal then move on to next entry;
 */

		if (!strcmp (new->name, ttyname (STDIN_FILENO))) 
		{
			if (flags & (BROADCAST_B_REMOTE)) 
			{
				continue;
			}
		}

/*
 * do legacy checks that may be redundant or unecessary or inaccurate. 
 */

		if (strstr (new->name, "/../")) 
		{
			continue;
		}
		if (!likeatty (new->name)) 
		{
			continue;
		}

/*
 * search list for old terminals having the new device name; if the 
 * only match is the new terminal then broadcast; do not broadcast  
 * to terminals twice; 
 */

		for (old = new->next; strcmp (old->name, new->name); old = old->next);
		if (old != new) 
		{
			continue;
		}

/*
 * the new terminal is unique in the list; spawn a child process to open it 
 * and write the message to it; timeouts or errors are handled by the child
 * process so the parent process proceeds without delay; 
 */

		count++;
		if (!fork ()) 
		{
			file_t fd = -1;
			struct sigaction sa;
			memset (&sa, 0, sizeof (sa));
			sa.sa_handler = broadcast_alarm_handler;
			sa.sa_flags = 0;
			sigemptyset (&sa.sa_mask);
			sigaction (SIGALRM, &sa, (struct sigaction *) (0));
			alarm (BROADCAST_T_TIMEOUT);
			if ((fd = open (old->name, O_WRONLY | O_NDELAY | O_NOCTTY)) != -1) 
			{
				if (isatty (fd)) 
				{
					if ((flags & BROADCAST_B_REPORT) != 0) 
					{
						error (0, 0, "Broadcast to %s", old->name);
					}
					write (fd, "\r\n", 2);
					write (fd, banner, strlen (banner));
					write (fd, string, strlen (string));
					write (fd, "\r\n", 2);
					write (fd, "\a", 1);
				}
				close (fd);
			}
			alarm (0);
			exit (0);
		}

/*
 * there is no need to add a new terminal to the list unless we tried to
 * broadcast to it; continue statements above correctly skip this part;
 */

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
	syslog (LOG_INFO, "Broadcast to %d terminal(s)", count);
	if (flags & BROADCAST_B_STATUS) 
	{
		error (0, 0, "Broadcast to %d terminal(s)", count);
	}
	return (count);
}


/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#endif

