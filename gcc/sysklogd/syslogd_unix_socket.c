/*====================================================================*
 *
 *   file_t syslogd_unix_socket(char const *device);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOGD_UNIX_SOCKET_SOURCE
#define SYSLOGD_UNIX_SOCKET_SOURCE

#include <unistd.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

#include "../linux/syslog.h"
#include "../sysklogd/syslogd.h"
#include "../tools/types.h"

#ifdef SYSLOGD_UNIXAF

file_t syslogd_unix_socket (struct sockaddr_un * sockaddr_un) 

{
	file_t fd;
	if (*sockaddr_un->sun_path == (char) (0)) 
	{
		errno = EINVAL;
		syslogd_error (errno, "Can't open socket file %s", sockaddr_un->sun_path);
		return (-1);
	}
	if (unlink (sockaddr_un->sun_path)) 
	{
		if (errno != ENOENT) 
		{
			syslogd_error (errno, "Can't remove socket file %s", sockaddr_un->sun_path);
			return (-1);
		}
	}
	if ((fd = socket (AF_UNIX, SOCK_DGRAM, 0)) == -1) 
	{
		syslogd_error (errno, "Can't allocate socket for %s", sockaddr_un->sun_path);
		return (-1);
	}
	if (bind (fd, (struct sockaddr *) (sockaddr_un), sizeof (sockaddr_un->sun_family) + strlen (sockaddr_un->sun_path)) == -1) 
	{
		syslogd_error (errno, "Can't bind socket to %s", sockaddr_un->sun_path);
		close (fd);
		return (-1);
	}
	if (chmod (sockaddr_un->sun_path, 0666) == -1) 
	{
		syslogd_error (errno, "Can't set %s file permissions", sockaddr_un->sun_path);
		close (fd);
		return (-1);
	}
	return (fd);
}


#endif
#endif

