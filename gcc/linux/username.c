/*====================================================================*
 *
 *   char const * username (pid_t uid);
 *   
 *   return the address of the username string associated with a uid; 
 *   the string is updated after each call but preserved with uid -1;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef USERNAME_SOURCE
#define USERNAME_SOURCE

#include <unistd.h>

#include "../linux/linux.h"
#include "../tools/sizes.h"

char const * username (uid_t uid) 

{
	static char buffer [USERNAME_MAX];
	if (uid != (uid_t)(-1)) 
	{
		getusername (buffer, sizeof (buffer), uid);
	}
	return (buffer);
}


#endif

