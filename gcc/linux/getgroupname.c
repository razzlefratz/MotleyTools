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
	struct group * group;

#ifdef CMASSOC_PARANOID

	if (getuid ()) 
	{
		errno = EPERM;
		return (-1);
	}

#endif
#ifdef CMASSOC_SAFEMODE

	if (!buffer) 
	{
		errno = EFAULT;
		return (-1);
	}
	if (!length) 
	{
		errno = EFAULT;
		return (-1);
	}

#endif

	if ((group = getgrgid (gid)) == (struct group *) (0)) 
	{
		errno = EINVAL;
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

