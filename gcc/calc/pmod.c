/*====================================================================*
 *
 *   unsigned pmod(signed domain, unsigned range);
 *
 *   calc.h
 *
 *   compute a positive integer such that 0 <= n < range; this function
 *   is identical to the modulo function for positive domain values but
 *   differs for even multiples of range and negative domain values;
 *
 *   illustration using a range of 4;
 *
 *   domain = ...  -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, ...
 *   modulo = ...  -2, -1,  0, -3, -2, -1, 0, 1, 2, 3, 0, 1, 2, ...
 *   qmod   = ...   2,  3,  4,  1,  2,  3, 4, 1, 2, 3, 4, 1, 2, ...
 *   pmod   = ...   2,  3,  0,  1,  2,  3, 0, 1, 2, 3, 0, 1, 2, ...
 *
 *   pmod() can be used to limit positive and negative array indices to
 *   values within the array bounds; for example, in a 20 element array,
 *   declared as "array[20]", "array[pmod(-33,20)]" refers to the 7th
 *   element;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef PMOD_SOURCE
#define PMOD_SOURCE

#include "../calc/calc.h"

unsigned pmod (register signed domain, register signed range) 

{
	domain %= range;
	if (range < 0) 
	{
		return ((domain < 0)? (domain - range): (domain));
	}
	if (range > 0) 
	{
		return ((domain < 0)? (domain + range): (domain));
	}
	return (0);
}


#endif

