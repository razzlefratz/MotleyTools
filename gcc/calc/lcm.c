/*====================================================================*
 *
 *   long lcm (long y, long y);
 *
 *   calc.h
 *
 *   compute the least common multiple of two long integers;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef LCM_SOURCE
#define LCM_SOURCE

#include "../calc/calc.h"

long lcm (long x, long y) 

{
	return ((x * y) / gcd (x, y));
}


#endif

