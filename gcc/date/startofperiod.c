/*====================================================================*
 *
 *   time_t startofperiod (time_t now, time_t due, int period);
 *
 *   compute the last or next due date relative to the current date;
 *
 *   now is the present date; due is any past or future date marking
 *   the start of a recurring period in days; 
 *
 *   given any due date and the positive period compute the next due
 *   date; given the negative period compute the last due date; 
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STARTOFPERIOD_SOURCE
#define STARTOFPERIOD_SOURCE

#include <time.h>

#include "../date/date.h"

time_t startofperiod (time_t now, time_t due, int period) 

{
	extern long timezone;
	if (period == 0) 
	{
		return (now);
	}
	now -= now % 86400 - timezone;
	due -= due % 86400 - timezone;
	due -= now;
	due %= (long)(period) * 86400;
	due += now;
	if ((period > 0) && (now > due)) 
	{
		due += (long)(period) * 86400;
	}
	if ((period < 0) && (now < due)) 
	{
		due += (long)(period) * 86400;
	}
	return (due);
}


#endif

