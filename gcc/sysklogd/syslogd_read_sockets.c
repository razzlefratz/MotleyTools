/*====================================================================*
 *
 *   void syslogd_read_sockets (struct socket *sockets);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOGD_READ_SOCKETS_SOURCE
#define SYSLOGD_READ_SOCKETS_SOURCE

#include <sys/un.h>
#include <errno.h>

#include "../linux/syslog.h"
#include "../sysklogd/syslogd.h"

void syslogd_read_sockets (struct socket * sockets) 

{ 

#ifdef SYSLOGD_UNIXAF

	extern char const * host_name; 

#endif
#ifdef SYSLOGD_INETAF

	extern char const * ourhosts []; 
	extern char const * ourdomains []; 

#endif

	struct socket * socket = sockets; 
	struct timeval timer = 
	{ 
		10, 
		0
	}; 
	fd_set readfds; 
	file_t fdrange = 0; 
	signed count; 

#if SYSLOGD_TRACE

	trace_enter ("syslogd_read_sockets"); 

#endif

	FD_ZERO (& readfds); 
	do 
	{ 
		socket = socket->next; 
		if (socket->desc < 0) 
		{ 
			continue; 
		} 
		FD_SET (socket->desc, & readfds); 
		if (socket->desc > fdrange) 
		{ 
			fdrange = socket->desc + 1; 
		} 
	} 
	while (socket != sockets); 
	count = select (fdrange, & readfds, (fd_set *) (0), (fd_set *) (0), & timer); 
	if (count > 0) 
	{ 
		do 
		{ 
			socket = socket->next; 
			if (socket->desc < 0) 
			{ 
				continue; 
			} 
			if (socket->sockaddr == (struct sockaddr *) (0)) 
			{ 
				syslogd_error (EINVAL, "No socket address"); 
				continue; 
			} 
			if (FD_ISSET (socket->desc, & readfds)) 
			{ 
				char const * origin; 
				char buffer [TEXTLINE_MAX + 1]; 
				signed length; 

#ifdef SYSLOGD_INETAF

				if (socket->sockaddr->sa_family == AF_INET) 
				{ 
					struct sockaddr_in * sockaddr_in = (struct sockaddr_in *) (socket->sockaddr); 
					length = recvfrom (socket->desc, buffer, sizeof (buffer), (flag_t) (0), socket->sockaddr, & socket->socksize); 
					if (length < 0) 
					{ 
						if (errno != EINTR) 
						{ 
							getsocketname (buffer, sizeof (buffer), sockaddr_in); 
							syslogd_error (errno, "Can't read %s with descriptor %d", buffer, socket->desc); 
						} 
						continue; 
					} 
					origin = syslogd_gethost (sockaddr_in, ourhosts, ourdomains); 
				} 

#endif
#ifdef SYSLOGD_UNIXAF

				if (socket->sockaddr->sa_family == AF_UNIX) 
				{ 
					struct sockaddr_un * sockaddr_un = (struct sockaddr_un *) (socket->sockaddr); 
					length = recv (socket->desc, buffer, sizeof (buffer), (flag_t) (0)); 
					if (length < 0) 
					{ 
						if (errno != EINTR) 
						{ 
							syslogd_error (errno, "Can't read %s with descriptor %d", sockaddr_un->sun_path, socket->desc); 
						} 
						continue; 
					} 
					origin = host_name; 
				} 

#endif

				if (length > 0) 
				{ 
					if (length < sizeof (buffer)) 
					{ 
						buffer [length++] = (char) (0); 
					} 
					syslogd_merge (socket, origin, buffer, length); 
					continue; 
				} 
			} 
		} 
		while (socket != sockets); 
	} 
	if (count < 0) 
	{ 
		if (errno != EINTR) 
		{ 
			syslogd_error (errno, "select"); 
		} 
	} 

#if SYSLOGD_TRACE

	trace_leave ("syslogd_read_sockets"); 

#endif

	return; 
} 

#endif



