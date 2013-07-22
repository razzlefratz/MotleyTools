/*====================================================================*
 *
 *   void syslogd_close_sockets (struct socket *sockets);
 *
 *   close open sockets; this stops incoming messages from external
 *   sources but syslogd can still post outgoing messages until all
 *   syslogs are closed; 
 *
 *   visit sockets having valid descriptors and address structures;
 *   create an alias pointer for the correct address structure type
 *   then close the socket; for simplicity, alias pointers have the
 *   same name as the structures they point to; 
 *
 *   think of it as having a cat named 'cat' and a dog name 'dog';
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOGD_CLOSE_SOCKETS_SOURCE
#define SYSLOGD_CLOSE_SOCKETS_SOURCE

#include <unistd.h>
#include <sys/un.h>
#include <errno.h>

#include "../linux/syslog.h"
#include "../sysklogd/syslogd.h"
#include "../tools/sizes.h"

void syslogd_close_sockets (struct socket * sockets) 

{ 
	struct socket * socket = sockets; 
	char buffer [HOSTADDR_MAX]; 

#if SYSLOGD_TRACE

	trace_enter ("syslogd_close_sockets"); 

#endif

	do 
	{ 
		socket = socket->next; 
		if (socket->desc < 0) 
		{ 
			continue; 
		} 
		if (socket->sockaddr == (struct sockaddr *) (0)) 
		{ 
			syslogd_error (EINVAL, "Invalid socket address structure"); 
			continue; 
		} 

#ifdef SYSLOGD_UNIXAF

		if (socket->sockaddr->sa_family == AF_UNIX) 
		{ 
			struct sockaddr_un * sockaddr_un = (struct sockaddr_un *) (socket->sockaddr); 
			syslogd_print (SYSLOG_SYSLOG | SYSLOG_NOTICE, "Closing host connection on %s", sockaddr_un->sun_path); 
			close (socket->desc); 
			if (unlink (sockaddr_un->sun_path)) 
			{ 
				syslogd_error (errno, "Can't remove socket %s", sockaddr_un->sun_path); 
			} 
			socket->desc = - 1; 
			continue; 
		} 

#endif
#ifdef SYSLOGD_INETAF

		if (socket->sockaddr->sa_family == AF_INET) 
		{ 
			struct sockaddr_in * sockaddr_in = (struct sockaddr_in *) (socket->sockaddr); 
			getsocketname (buffer, sizeof (buffer), sockaddr_in); 
			syslogd_print (SYSLOG_SYSLOG | SYSLOG_NOTICE, "Closing inet connection on %s", buffer); 
			close (socket->desc); 
			socket->desc = - 1; 
			continue; 
		} 

#endif

	} 
	while (socket != sockets); 

#if SYSLOGD_TRACE

	trace_leave ("syslogd_close_sockets"); 

#endif

	return; 
} 

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif



