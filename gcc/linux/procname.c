/*====================================================================*
 *
 *   char *procname (pid_t pid);
 *   
 *   linusx.h
 *
 *   return process name associated with a pid; the result is stored 
 *   internally and replaced with each call; however the last result
 *   is returned for pid -1;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef PROCNAME_SOURCE
#define PROCNAME_SOURCE

#include <unistd.h>

#include "../linux/linux.h"
#include "../tools/sizes.h"

char *procname (pid_t pid) 

{
	static char buffer [PROCNAME_MAX];
	if (pid != (pid_t)(-1)) 
	{
		getprocname (buffer, sizeof (buffer), pid);
	}
	return (buffer);
}


#endif

