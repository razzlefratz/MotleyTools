/*====================================================================*
 *
 *   signal_t signalspec (char const *string);
 *
 *   signals.h
 *
 *   return the signal number represented by a string; the string
 *   may be numeric or alphanumeric; numeric strings must be only
 *   decimnal digits; alpahnumeric strings must be a valid signal
 *   name in upper case; return -1 on failure; 
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SIGNALSPEC_SOURCE
#define SIGNALSPEC_SOURCE

#include <signal.h>
#include <ctype.h>
#include <error.h>
#include <errno.h>

#include "../linux/signals.h"

signal_t signalspec (char const *string) 

{
	signal_t signo = 0;
	char const *sp;
	if (string == (char *) (0)) 
	{
		error (1, EINVAL, "signal is null");
	}
	for (sp = string; isdigit (*sp); signo = (signo * 10) + (*sp++ - '0'));
	if (*sp != (char) (0)) 
	{
		signo = signalcode (string);
	}
	if ((signo < SIGHUP) || (signo > SIGSYS)) 
	{
		error (1, EINVAL, "signal %s is unsupported", string);
	}
	return (signo);
}


#endif

