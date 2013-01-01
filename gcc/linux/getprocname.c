/*====================================================================*
 *
 *   int getprocname (char buffer[], size_t length, pid_t pid);
 *   
 *   linux.h
 *
 *   return process name for a given process identifier;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef GETPROCNAME_SOURCE
#define GETPROCNAME_SOURCE

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

#include "../linux/linux.h"
#include "../tools/sizes.h"

int getprocname (char buffer [], size_t length, pid_t pid) 

{
	char filename [FILENAME_MAX];
	signed fd;

#ifdef CMASSOC_PARANOID

	if (getuid ()) 
	{
		errno = EPERM;
		return (-1);
	}

#endif
#ifdef CMASSOC_SAFEMODE

	if (buffer == (char *) (0)) 
	{
		errno = EFAULT;
		return (-1);
	}

#endif

	if (length > 0) 
	{
		snprintf (filename, sizeof (filename), "/proc/%d/stat", pid);
		if ((fd = open (filename, O_RDONLY)) == -1) 
		{
			errno = EINVAL;
			return (-1);
		}
		while ((read (fd, buffer, 1) > 0) && (*buffer != '('));
		while ((read (fd, buffer, 1) > 0) && (*buffer != ')')) 
		{
			if (length > 1) 
			{
				buffer++;
				length--;
			}
		}
		*buffer = (char) (0);
		close (fd);
	}
	return (0);
}


#endif

