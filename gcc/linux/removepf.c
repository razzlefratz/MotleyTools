/*====================================================================*
 *   
 *   int removepf (char const *filename);
 *
 *   remove a pidfile (or any other file, for that matter); included
 *   for pidfile library copleteness and to provide a hook for debug 
 *   purposes;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef REMOVEPF_SOURCE
#define REMOVEPF_SOURCE

#include <unistd.h>
#include <error.h>
#include <errno.h>

#include "../linux/pidfile.h"

int removepf (char const *filename) 

{
	if (unlink (filename)) 
	{
		error (0, errno, "can't unlink pidfile %s", filename);
		return (-1);
	}
	return (0);
}


#endif

