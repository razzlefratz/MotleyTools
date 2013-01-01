/*====================================================================*
 *
 *   pid_t readpf (char const *filename);
 *
 *   pidfile.h
 *
 *   read a pidfile and return the stored pid; return 0 if the file 
 *   is missing, unreadable or empty; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef READPF_SOURCE
#define READPF_SOURCE

#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>

#include "../linux/pidfile.h"
#include "../tools/types.h"

pid_t readpf (char const *filename) 

{
	pid_t pid = (pid_t) (0);
	file_t fd;
	if ((fd = open (filename, O_RDONLY)) != -1) 
	{
		char c;
		while ((read (fd, &c, 1) > 0) && isdigit (c)) 
		{
			pid *= 10;
			pid += (pid_t)(c - '0');
		}
		close (fd);
	}
	return (pid);
}


#endif

