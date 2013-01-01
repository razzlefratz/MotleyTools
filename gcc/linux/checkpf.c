/*====================================================================*
 *
 *    pid_t checkpf (char const *filename);
 *
 *    pidfile.h
 *
 *    read a pidfile to determine if that process is still active; 
 *    return the PID if active or (pid_t)(0) if not; also, return
 *    0 if the pid is that of the current process; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CHECKPF_SOURCE
#define CHECKPF_SOURCE

#include <unistd.h>
#include <signal.h>
#include <error.h>
#include <errno.h>

#include "../linux/pidfile.h"

pid_t checkpf (char const *filename) 

{
	pid_t pid = readpf (filename);
	if ((pid != 0) && (pid != getpid ())) 
	{
		if (kill (pid, 0) && (errno == ESRCH)) 
		{
			return ((pid_t) (0));
		}
	}
	return (pid);
}


#endif

