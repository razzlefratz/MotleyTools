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
	struct passwd *passwd;

#ifdef CMASSOC_PARANOID

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
	if (length > sizeof (passwd->pw_name)) 
	{
		length = sizeof (passwd->pw_name);
	}
	if (length > 0) 
	{
		memcpy (buffer, passwd->pw_name, length);
		buffer [length] = (char)(0);
	}
	return (0);
}


#endif

