/*====================================================================*
 *
 *   time_t midnight (time_t when);
 *   
 *   convert a date and time, expressed as seconds since the epoch
 *   on 01 jan 1970 00:00:00, to the number of seconds to midnight
 *   on that date; this sets the hours, minutes and seconds to 00;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MIDNIGHT_SOURCE
#define MIDNIGHT_SOURCE

#include <time.h>

#include "../date/date.h"

time_t midnight (time_t when) 

{
	extern long timezone;
	return (when - when % SECONDS_IN_DAY + timezone);
}


#endif

