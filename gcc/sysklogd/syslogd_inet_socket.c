/*====================================================================*
 *
 *   int syslogd_inet_socket (int port);
 *
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOGD_INET_SOCKET_SOURCE
#define SYSLOGD_INET_SOCKET_SOURCE

#include <unistd.h>
#include <sys/socket.h>
#include <errno.h>

#include "../linux/syslog.h"
#include "../sysklogd/syslogd.h"
#include "../tools/types.h"
#include "../tools/sizes.h"

#ifdef SYSLOGD_INETAF

file_t syslogd_inet_socket (struct sockaddr_in * sockaddr_in) 

{ 
	char buffer [HOSTADDR_MAX]; 
	bool_t state = true; 
	file_t fd; 
	if ((fd = socket (AF_INET, SOCK_DGRAM, 0)) == - 1) 
	{ 
		getsocketname (buffer, sizeof (buffer), sockaddr_in); 
		syslogd_error (errno, "Can't allocate socket for %s", buffer); 
		return (- 1); 
	} 
	if (setsockopt (fd, SOL_SOCKET, SO_REUSEADDR, (char *) (& state), sizeof (state)) == - 1) 
	{ 
		getsocketname (buffer, sizeof (buffer), sockaddr_in); 
		syslogd_error (errno, "Can't set socket options for %s", buffer); 
		close (fd); 
		return (- 1); 
	} 
	if (bind (fd, (struct sockaddr *) (sockaddr_in), sizeof (struct sockaddr_in)) == - 1) 
	{ 
		getsocketname (buffer, sizeof (buffer), sockaddr_in); 
		syslogd_error (errno, "Can't connect to %s", buffer); 
		close (fd); 
		return (- 1); 
	} 
	return (fd); 
} 

#endif
#endif



