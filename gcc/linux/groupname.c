/*====================================================================*
 *
 *   char *groupname (gid_t gid);
 *   
 *   return the address of the username string associated with a uid; 
 *   the string is updated after each call but preserved with uid -1;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef GROUPNAME_SOURCE
#define GROUPNAME_SOURCE

#include <unistd.h>

#include "../linux/linux.h"
#include "../tools/sizes.h"

char const * groupname (gid_t gid) 

{
	static char buffer [USERNAME_MAX];
	if (gid != (gid_t)(-1)) 
	{
		getgroupname (buffer, sizeof (buffer), gid);
	}
	return (buffer);
}


#endif

