/*====================================================================*
 *
 *   void syslogd_open_sockets();
 *
 *   open configured unix and/or inet domain sockets; this enables
 *   message receipt from external sources (other programs) but it
 *   does not guarantee that they will be posted; the syslog queue
 *   must be started for that to happen; 
 *    
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOGD_OPEN_SOCKETS_SOURCE
#define SYSLOGD_OPEN_SOCKETS_SOURCE

#include <errno.h>
#include <sys/un.h>

#include "../linux/syslog.h"
#include "../sysklogd/syslogd.h"
#include "../tools/sizes.h"

void syslogd_open_sockets (struct socket *sockets) 

{
	struct socket *socket = sockets;

#if SYSLOGD_TRACE

	trace_enter ("syslogd_open_sockets");

#endif

	do 
	{
		socket = socket->next;
		if (socket->desc != -1) 
		{
			continue;
		}
		if (socket->sockaddr == (struct sockaddr *)(0)) 
		{
			syslogd_error (EINVAL, "Missing socket address");
			continue;
		}

#ifdef SYSLOGD_UNIXAF

		if (socket->sockaddr->sa_family == AF_UNIX) 
		{
			struct sockaddr_un * sockaddr_un = (struct sockaddr_un *)(socket->sockaddr);
			syslogd_print (SYSLOG_SYSLOG | SYSLOG_NOTICE, "Opening host connection on %s", sockaddr_un->sun_path);
			socket->desc = syslogd_unix_socket (sockaddr_un);
			continue;
		}

#endif
#ifdef SYSLOGD_INETAF

		if (socket->sockaddr->sa_family == AF_INET) 
		{
			char buffer [HOSTADDR_MAX];
			struct sockaddr_in * sockaddr_in = (struct sockaddr_in *)(socket->sockaddr);
			getsocketname (buffer, sizeof (buffer), sockaddr_in);
			syslogd_print (SYSLOG_SYSLOG | SYSLOG_NOTICE, "Opening inet connection on %s", buffer);
			socket->desc = syslogd_inet_socket (sockaddr_in);
			continue;
		}

#endif

	}
	while (socket != sockets);

#if SYSLOGD_TRACE

	trace_leave ("syslogd_open_sockets");

#endif

	return;
}


#endif

