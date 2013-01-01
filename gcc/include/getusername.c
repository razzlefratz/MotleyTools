/*====================================================================*
 *
 *   int getusername (char buffer[], size_t length, uid_t uid);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef GETUSERNAME_SOURCE
#define GETUSERNAME_SOURCE

#include <sys/types.h>
#include <errno.h>
#include <pwd.h>

#include "../linux/linux.h"

int getusername (char buffer [], size_t length, uid_t uid) 

{
	struct passwd *passwd;

#ifdef CMASSOC_SECURE

	if (getuid ()) 
	{
		errno = EPERM;
		return (-1);
	}

#endif
#ifdef CMASSOC_SAFEMODE

	if (buffer == (char) (0)) 
	{
		errno = EFAULT;
		return (-1);
	}

#endif

	if ((passwd = getpwuid (uid)) == (struct passwd *) (0)) 
	{
		errno = EINVAL;
		return (-1);
	}
	if (length-- > 0) 
	{
		size_t offset;
		for (offset = 0; offset < length; offset++) 
		{
			buffer [offset] = passwd->pw_name [offset];
		}
		buffer [offset] = (char) (0);
	}
	return (0);
}


#endif

