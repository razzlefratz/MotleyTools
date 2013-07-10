/*====================================================================*
 *
 *   shout.c - send broadcast message to all users; 
 *
 *.  Released 2005 by Charles Maier Associates Ltd for private use;
 *:  Licensed under GNU General Public License version 2 and later;
 *;  Designed for CMLinux based on LFS and Debian GNU/Linux;
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <syslog.h>
#include <errno.h>
#include <pwd.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../linux/linux.h"
#include "../linux/broadcast.h"
#include "../linux/syslog.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/emalloc.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../linux/broadcast.c"
#include "../linux/syslog_basic.c"
#include "../linux/syslog_error.c"
#endif

/*====================================================================*
 *   
 *   int main(int argc, char **argv);
 *   
 *--------------------------------------------------------------------*/

int main (int argc, const char * argv []) 

{ 
	extern const char * program_name; 
	static const char * optv [] = 
	{ 
		"bcnrt", 
		"message [message] [...] or [< stdin]", 
		"broadcast a message on all terminals", 
		"b\tprint each argument as one bullet point", 
		"n\tdiscard broadcast preamble for root only", 
		"c\tdisplay broadcast terminal count", 
		"t\tdisplay broadcast terminal names", 
		"r\tbroadcast on remote terminals only", 
		(const char * ) (0)
	}; 
	flag_t flags = BROADCAST_B_BANNER; 
	char message [BROADCAST_MAXCHARS] = ""; 
	size_t nlines = 0; 
	size_t nchars = 0; 
	signed c; 
	optind = 1; 
	opterr = 1; 
	while ((c = getoptv (argc, argv, optv)) != - 1) 
	{ 
		switch (c) 
		{ 
		case 'n': 
			_clrbits (flags, BROADCAST_B_BANNER); 
			if (getuid ()) 
			{ 
				error (1, EPERM, "can't suppress the broadcast banner"); 
			} 
			break; 
		case 'r': 
			_setbits (flags, BROADCAST_B_REMOTE); 
			break; 
		case 'b': 
			_setbits (flags, BROADCAST_B_BULLET); 
			break; 
		case 't': 
			_setbits (flags, BROADCAST_B_REPORT); 
			break; 
		case 'c': 
			_setbits (flags, BROADCAST_B_STATUS); 
			break; 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 
	openlog (program_name, 0, LOG_USER | LOG_INFO); 
	if (geteuid ()) 
	{ 
		syslog_error (LOG_NOTICE, EPERM, "user %s tried to broadcast", getlogin ()); 
		error (1, EPERM, NOTROOT); 
	} 
	if (! argc) 
	{ 
		if ((nchars = read (STDIN_FILENO, message, sizeof (message)- 1)) != - 1) 
		{ 
			message [nchars]= (char)(0); 
		} 
	} 
	while ((argc) && (* argv)) 
	{ 
		if (_anyset (flags, BROADCAST_B_BULLET)) 
		{ 
			message [nchars++ ] = ' '; 
			message [nchars++ ] = '-'; 
			message [nchars++ ] = ' '; 
		} 
		nchars += snprintf (message + nchars, BROADCAST_MAXCHARS - nchars, "%s\n", * argv); 
		argc-- ; 
		argv++ ; 
	} 
	for (nchars = 0; (message [nchars] != (char) (0)) && (nchars < BROADCAST_MAXCHARS) && (nlines < BROADCAST_MAXLINES); nchars++ ) 
	{ 
		if (message [nchars] == '\n') 
		{ 
			nlines++ ; 
		} 
	} 
	message [nchars] = (char)(0); 
	syslog (LOG_SYSLOG | LOG_INFO, "user %s broadcast %d line(s) total %d char(s)", getlogin (), nlines, nchars); 
	unsetenv ("TZ"); 
	broadcast (message, flags); 
	closelog (); 
	exit (0); 
} 

