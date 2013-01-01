/*====================================================================*
 *
 *   unsigned dayofwk(unsigned yr, signed mo, signed dt)
 *
 *   date.h
 *
 *   return the weekday for a given date as integer 0 thru 6; the
 *   month and date are specified as zero based integers; this is
 *   done to support values in struct tm as defined in time.h; 
 *
 *   the function value can be the index into the string vector
 *   sv_wkday[] to retrieve the weekday name string;
 *
 *      0=sunday, 1=monday, ... 6=saturday;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef DAYOFWK_SOURCE
#define DAYOFWK_SOURCE

#include "../date/date.h"

unsigned dayofwk (register unsigned yr, register signed mo, register signed dy) 

{
	register int cn;
	mo += yr * MONTHS_IN_YEAR;
	yr = mo / MONTHS_IN_YEAR;
	mo = mo % MONTHS_IN_YEAR;
	if (mo > 1) 
	{
		--mo;
	}
	else 
	{
		mo += MONTHS_IN_YEAR;
		--mo;
		--yr;
	}
	cn = yr / YEARS_IN_CENTURY;
	yr = yr % YEARS_IN_CENTURY;
	dy += (26 * mo - 1) / 10 + (5 * yr) / 4 + cn / 4 - 2 * cn + 1;
	dy %= DAYS_IN_WEEK;
	return ((dy < 0)? (dy + DAYS_IN_WEEK): (dy));
}


#endif

