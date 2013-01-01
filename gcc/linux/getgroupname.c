/*====================================================================*
 *
 *   int getgroupname (char buffer[], size_t length, gid_t gid);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef GETGROUPNAME_SOURCE
#define GETGROUPNAME_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <grp.h>

#include "../linux/linux.h"

int getgroupname (char buffer [], size_t length, gid_t gid) 

{
	struct group *group;

#ifdef CMASSOC_SAFEMODE

	if (buffer == (char *) (0)) 
	{
		return (-1);
	}

#endif

	if ((group = getgrgid (gid)) == (struct group *) (0)) 
	{
		return (-1);
	}
	if (length-- > 0) 
	{
		size_t offset = 0;
		for (offset = 0; offset < length; offset++) 
		{
			buffer [offset] = group->gr_name [offset];
		}
		buffer [offset] = (char) (0);
	}
	return (0);
}


#endif

