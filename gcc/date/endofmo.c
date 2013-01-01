/*====================================================================*
 *
 *   unsigned endofmo(unsigned yr, signed mo)
 *
 *   return the last date of the given month when the year is known; 
 *   the month is an integer 0 to 11;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ENDOFMO_SOURCE
#define ENDOFMO_SOURCE

#include "../date/date.h"

unsigned endofmo (register unsigned yr, register signed mo) 

{
	static unsigned days [12] = 
	{
		31,
		28,
		31,
		30,
		31,
		30,
		31,
		31,
		30,
		31,
		30,
		31
	};
	register unsigned count;
	mo += yr * MONTHS_IN_YEAR;
	yr = mo / MONTHS_IN_YEAR;
	mo = mo % MONTHS_IN_YEAR;
	count = days [mo];
	if ((mo == 1) && isleap (yr)) 
	{
		count++;
	}
	return (count);
}


#endif

