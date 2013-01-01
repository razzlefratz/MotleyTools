/*====================================================================*
 *
 *   unsigned qmod(signed domain, signed range);
 *
 *   calc.h
 *
 *   this cyclic function returns a positive integer 0 < n <= range; it
 *   is identical to the modulo function for positive domain values and
 *   even multiples of the range but differs for negative domain values;
 *
 *   illustration using a range of 4;
 *
 *   domain = ...  -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, ...
 *   modulo = ...  -2, -1,  0, -3, -2, -1, 0, 1, 2, 3, 0, 1, 2, ...
 *   qmod   = ...   2,  3,  4,  1,  2,  3, 4, 1, 2, 3, 4, 1, 2, ...
 *   pmod   = ...   2,  3,  0,  1,  2,  3, 0, 1, 2, 3, 0, 1, 2, ...
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef QMOD_SOURCE
#define QMOD_SOURCE

#ifndef QMOD_SOURCE
#define QMOD_SOURCE

#include "../calc/calc.h"

unsigned qmod (register signed domain, register signed range) 

{
	domain %= range;
	if (range < 0) 
	{
		return ((domain > 0)? (domain): (domain - range));
	}
	if (range > 0) 
	{
		return ((domain > 0)? (domain): (domain + range));
	}
	return (0);
}


#endif

#endif

