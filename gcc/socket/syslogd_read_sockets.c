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
	struct socket * socket = sockets;
	struct timeval timer = 
	{
		10,
		0
	};
	fd_set readfds;
	file_t fdrange = 0;
	signed count;
	FD_ZERO (&readfds);
	do 
	{
		socket = socket->next;
		if (socket->desc < 0) 
		{
			continue;
		}
		FD_SET (socket->desc, &readfds);
		if (socket->desc > fdrange) 
		{
			fdrange = socket->desc + 1;
		}
	}
	while (socket != sockets);
	count = select (fdrange, &readfds, (fd_set *) (0), (fd_set *) (0), &timer);
	if (count > 0) 
	{
		do 
		{
			socket = socket->next;
			if (socket->desc < 0) 
			{
				continue;
			}
			if (!socket->sockaddr) 
			{
				continue;
			}
			if (FD_ISSET (socket->desc, &readfds)) 
			{
				struct sockaddr_un * sockaddr_un = (struct sockaddr_un *) (socket->sockaddr);
				char const * origin = host_name;
				char buffer [TEXTLINE_MAX + 1];
				signed length = recv (socket->desc, buffer, sizeof (buffer), (flag_t) (0));
				if (length < 0) 
				{
					if (errno != EINTR) 
					{
						error (0, errno, "Can't read %s with descriptor %d", sockaddr_un->sun_path, socket->desc);
					}
					continue;
				}
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
	return;
}


#endif

