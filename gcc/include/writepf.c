/*====================================================================*
 *
 *   pid_t writepf (char const *filename);
 *
 *   write the current process pid to file and return the pid or
 *   0 on error;
 *
 *   the PID is encoded right to left, buffer end to buffer start; a
 *   newline is inserted then the digits; this elminates the need to
 *   reverse the string after conversion; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef WRITEPF_SOURCE
#define WRITEPF_SOURCE

#include <unistd.h>
#include <sys/file.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

#include "../linux/pidfile.h"
#include "../tools/error.h"

int writepf (char const *filename) 

{
	char buffer [16];
	int column = sizeof (buffer);
	pid_t pid = getpid ();
	int fd;
	if ((fd = open (filename, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) 
	{
		error (0, errno, "can't open pidfile %s.", filename);
		return (0);
	}
	if (flock (fd, LOCK_EX | LOCK_NB) == -1) 
	{
		error (0, errno, "can't lock pidfile %s", filename);
		close (fd);
		return (0);
	}
	for (buffer [--column] = '\n'; (column > 0) && (pid > 0); pid /= 10) 
	{
		buffer [--column] = '0' + pid % 10;
	}
	if (write (fd, buffer + column, sizeof (buffer) - column) != (signed)(sizeof (buffer) - column)) 
	{
		error (0, errno, "can't write pidfile %s", filename);
		close (fd);
		return (0);
	}
	if (flock (fd, LOCK_UN) == -1) 
	{
		error (0, errno, "can't unlock pidfile %s", filename);
		close (fd);
		return (0);
	}
	close (fd);
	return (-1);
}


#endif

