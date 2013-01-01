/*====================================================================*
 *
 *   int strfpid (char buffer[], size_t length, pid_t pid);
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

#ifndef STRFPID_SOURCE
#define STRFPID_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include "../linux/linux.h"
#include "../tools/sizes.h"

size_t strfpid (char buffer [], size_t length, pid_t pid) 

{
	char filename [FILENAME_MAX];
	char *string = buffer;
	signed fd;
	if (buffer == (char *) (0)) 
	{
		return (0);
	}
	buffer += length;
	if (string < buffer) 
	{
		snprintf (filename, sizeof (filename), "/proc/%d/stat", pid);
		if ((fd = open (filename, O_RDONLY)) == -1) 
		{
			return (0);
		}
		while ((read (fd, string, 1) > 0) && (*string != '('));
		while ((read (fd, string, 1) > 0) && (*string != ')')) 
		{
			if (string < buffer) 
			{
				string++;
			}
		}
		*string = (char) (0);
		close (fd);
	}
	buffer -= length;
	return (string - buffer);
}


#endif

