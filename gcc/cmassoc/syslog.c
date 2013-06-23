/*====================================================================*
 *
 *   syslog.c
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../files/files.h"
#include "../linux/syslog.h"
#include "../date/date.h"

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../sysklogd/syslog_facility_codes.c"
#include "../sysklogd/syslog_severity_codes.c"
#include "../sysklogd/syslog_encode.c"
#include "../sysklogd/syslog_lookup.c"
#endif

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../linux/syslog_basic.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define SYSLOG_B_BASENAME (1 << 0)

/*====================================================================*
 *
 *   void mysyslogtest (facility_t facility);
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void mysyslogtest (int priority) 

{
	facility_t facility = priority & SYSLOG_FACILITY_MASK;
	syslog (facility | SYSLOG_EMERG, "sample emergency message");
	syslog (facility | SYSLOG_ALERT, "sample alert message");
	syslog (facility | SYSLOG_CRIT, "sample critical message");
	syslog (facility | SYSLOG_ERR, "sample error message");
	syslog (facility | SYSLOG_WARNING, "sample warning message");
	syslog (facility | SYSLOG_NOTICE, "sample notice message");
	syslog (facility | SYSLOG_INFO, "sample information message");
	syslog (facility | SYSLOG_DEBUG, "sample debug messaage");
	return;
}

/*====================================================================*
 *
 *   file_t myopenlog (char const *socketname, int sockettype);
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static file_t myopenlog (char const * socketname, int sockettype) 

{
	static struct sockaddr_un sockaddr_un;
	file_t fd;
	sockaddr_un.sun_family = AF_UNIX;
	if (strlen (socketname) >= sizeof (sockaddr_un.sun_path)) 
	{
		error (1, ENAMETOOLONG, "can't open socket %s", socketname);
	}
	strcpy (sockaddr_un.sun_path, socketname);
	if ((fd = socket (AF_UNIX, sockettype, 0)) == -1) 
	{
		error (1, errno, "can't open socket %s", sockaddr_un.sun_path);
	}
	if (connect (fd, (struct sockaddr *) (& sockaddr_un), sizeof (sockaddr_un)) == -1) 
	{
		error (1, errno, "can't connect to socket %s", sockaddr_un.sun_path);
	}
	return (fd);
}

/*====================================================================*
 *
 *   void mysyslog (file_t fd, int options, int priority, char const *identity, char const *message);
 *
 *   format and write a syslog message string to fd;
 *
 *   <priority> logtime: identity (pid): message
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void mysyslog (file_t fd, int options, int priority, char const * identity, char const * message) 

{
	char buffer [TEXTLINE_MAX];
	time_t now = time (& now);
	size_t length = 0;
	if (fd != -1) 
	{
		length = snprintf (buffer + length, sizeof (buffer) - length, "<%d>", priority);
		length = strftime (buffer + length, sizeof (buffer) - length, LOGTIME, localtime (& now));
		length = snprintf (buffer + length, sizeof (buffer) - length, ": ");
		if (identity != (char *) (0)) 
		{
			length = snprintf (buffer + length, sizeof (buffer) - length, "%s", identity);
		}
		if (options & SYSLOG_PROCESS) 
		{
			length+= snprintf (buffer + length, sizeof (buffer) - length, "[%d]", getpid ());
		}
		if ((identity != (char *) (0)) || (options & SYSLOG_PROCESS)) 
		{
			length = snprintf (buffer + length, sizeof (buffer) - length, ": ");
		}
		length+= snprintf (buffer + length, sizeof (buffer) - length, "%s", message);
		length+= snprintf (buffer + length, sizeof (buffer) - length, "\n");
		if (write (fd, buffer, length) < length) 
		{
			error (0, errno, "can't write to syslog");
		}
	}
	return;
}

/*====================================================================*
 *   
 *   int main (int argc, char const * argv[]);
 *
 *   reads input and write to system log facility; 
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"b:def:i:p:ns:t",
		"[message]",
		"write a message to the system logging facility",
		"b s\tidentity is the basename of s ",
		"e\techo messages on stderr",
		"f s\tmessage filename",
		"i s\tidentity string",
		"p s\tpriority in facility.severity format",
		"n\tinclude PID number",
		"d\tuse datagrams",
		"s s\tsocket filename",
		"t\tsend test messages",
		(char const *) (0)
	};
	char message [TEXTLINE_MAX];
	char * bp = message;
	char const * socketname = (char *) (0);
	char const * identity = (char *)(0);
	int priority = SYSLOG_USER | SYSLOG_INFO;
	code_t sockettype = SOCK_STREAM;
	flag_t options = (flag_t) (0);
	file_t fd = (file_t) (-1);
	int c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'b':
			for (identity = optarg; * optarg != (char) (0); optarg++) 
			{
				if (* optarg == PATH_C_EXTENDER) 
				{
					identity = optarg + 1;
				}
			}
			break;
		case 'd':
			sockettype = SOCK_DGRAM;
			break;
		case 'e':
			_setbits (options, SYSLOG_PERROR);
			break;
		case 'f':
			if (freopen (optarg, "rb", stdin) == (FILE *) (0)) 
			{
				error (1, errno, "%s", optarg);
			}
			break;
		case 'i':
			identity = optarg;
			break;
		case 'n':
			_setbits (options, SYSLOG_PROCESS);
			break;
		case 'p':
			priority = syslog_encode (optarg);
			break;
		case 's':
			socketname = optarg;
			break;
		case 't':
			mysyslogtest (priority);
			exit (0);
		default:
			break;
		}
	}
	argc-= optind;
	argv+= optind;
	fclose (stdout);
	if (socketname) 
	{
		fd = myopenlog (socketname, sockettype);
	}
	else 
	{
		openlog (identity, options, priority);
	}
	if (!argc) 
	{
		while ((c = getc (stdin)) != EOF) 
		{
			if (nobreak (c)) 
			{
				if ((bp - message) < (sizeof (message) - 1)) 
				{
					* bp++ = c;
				}
			}
			else 
			{
				* bp = (char) (0);
				if (socketname) 
				{
					mysyslog (fd, options, priority, identity, message);
				}
				else 
				{
					syslog (priority, "%s", message);
				}
				bp = message;
			}
		}
	}
	else 
	{
		for (bp = message; (argc) && (* argv); * bp++ = ' ') 
		{
			char const * string;
			for (string = * argv; * string; string++) 
			{
				if ((bp - message) < (sizeof (message) - 1)) 
				{
					* bp++ = * string;
				}
			}
			argc--;
			argv++;
		}
		if (bp > message) 
		{
			bp--;
		}
		* bp = (char) (0);
		if (socketname) 
		{
			mysyslog (fd, options, priority, identity, message);
		}
		else 
		{
			syslog (priority, "%s", message);
		}
	}
	if (socketname) 
	{
		close (fd);
	}
	else 
	{
		closelog ();
	}
	exit (0);
}

