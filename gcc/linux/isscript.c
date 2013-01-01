/*====================================================================*
 *
 *   bool isscript (char const *filename);
 *
 *   linux.h
 *
 *   return true if filename contains a standard unix/linux srcipt
 *   where standard scripts start with "#!<pathname>";
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ISSCRIPT_SOURCE
#define ISSCRIPT_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "../linux/linux.h"
#include "../tools/types.h"

bool isscript (char const *filename) 

{
	signed fd;
	if ((fd = open (filename, O_RDONLY)) != -1) 
	{
		char buffer [2];
		read (fd, buffer, sizeof (buffer));
		close (fd);
		if ((buffer [0] == '#') && (buffer [1] == '!')) 
		{
			return (true);
		}
	}
	return (false);
}


#endif

