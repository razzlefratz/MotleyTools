/*====================================================================*
 *
 *   int getusername (char buffer[], size_t length, uid_t uid);
 *
 *   return a specific username based on the user ID;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef GETUSERNAME_SOURCE
#define GETUSERNAME_SOURCE

#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <pwd.h>

#include "../linux/linux.h"

int getusername (char buffer [], size_t length, uid_t uid) 

{
	struct passwd * passwd;

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

	if ((passwd = getpwuid (uid)) == (struct passwd *) (0)) 
	{
		errno = EINVAL;
		return (-1);
	}
	memset (buffer, 0, length);
	if (length-- > strlen (passwd->pw_name)) 
	{
		length = strlen (passwd->pw_name);
	}
	memcpy (buffer, passwd->pw_name, length);
	return (0);
}


#endif

