/*====================================================================*
 *
 *   char const * username (pid_t uid);
 *   
 *   return the urename associated with a uid; the result is stored
 *   internally and prelaced with each call; however, the last result
 *   is returned for uid -1;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef USERNAME_SOURCE
#define USERNAME_SOURCE

#include <sys/types.h>

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

