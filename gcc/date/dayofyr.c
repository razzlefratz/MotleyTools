/*====================================================================*
 *
 *   unsigned dayofyr(unsigned yr, unsigned mo, unsigned dt);
 *
 *  date.h
 *
 *   return the day of the year, also kown as the Julian Date;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../date/date.h"

unsigned dayofyr (unsigned yr, signed mo, signed dt) 

{
	static unsigned days [12] = 
	{
		0,
		31,
		59,
		90,
		120,
		151,
		181,
		212,
		243,
		273,
		304,
		334
	};
	unsigned count;
	mo += yr * MONTHS_IN_YEAR;
	yr = mo / MONTHS_IN_YEAR;
	mo = mo % MONTHS_IN_YEAR;
	count = days [mo - 1] + dt;
	if ((count > days [2]) && isleap (yr)) 
	{
		count++;
	}
	return (count);
}

