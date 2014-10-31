/*====================================================================*
 *
 *   signed timer (unsigned seconds);
 *
 *   timer.h
 *
 *   perform a named function; return 1 if it completes within the
 *   alloted time in seconds; return 0 if it does not; return -1 on
 *   timer error;
 *
 *   this is a demonstration function and will require modification
 *   depending on your application;
 *   
 *   Motley Tools by Charles Maier <cmaier@cmassoc.net>;
 *   Copyright 2001-2006 by Charles Maier Associates;
 *   Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

#ifndef TIMER_SOURCE
#define TIMER_SOURCE

#include <stdint.h>
#include <unistd.h>
#include <memory.h>
#include <string.h>
#include <sys/time.h>

#include "../tools/timer.h"
#include "../tools/error.h"
#include "../tools/flags.h"

signed timer (unsigned expire, int function ())

{
	struct timeval ts;
	struct timeval tc;
	unsigned timer;
	if (gettimeofday (& ts, NULL) == -1)
	{
		return (-1);
	}
	for (timer = 0; timer < expire; timer = SECONDS (ts, tc))
	{
		if (function ())
		{
			return (1);
		}
		if (gettimeofday (& tc, NULL) == -1)
		{
			return (-1);
		}
	}
	return (0);
}



#endif



