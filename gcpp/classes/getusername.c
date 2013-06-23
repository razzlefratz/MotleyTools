/*====================================================================*
 *
 *   int getusername (char buffer[], size_t length, uid_t uid);
 *
 *   return a specific username based on the user ID;
 *
 *.  copyright 2005 by charles maier associates limited as open source;
 *:  compiled for debian gnu/linux environment using gcc 2.95 compiler;
 *;  licensed under the terms of the GNU Public License; Version 2;
 *
 *--------------------------------------------------------------------*/
 
#ifndef GETUSERNAME_SOURCE
#define GETUSERNAME_SOURCE
 
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <pwd.h>
 
#include "../classes/linux.h"
 
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
		memcpy(buffer, passwd->pw_name, length);
		buffer [length] = (char)(0);
	}
	return (0); 
}

#endif

