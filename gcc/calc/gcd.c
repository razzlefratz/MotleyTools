/*====================================================================*
 *
 *   long gcd(long x, long y);
 *
 *   calc.h
 *
 *   Compute greatest common divisor of two integers using Euclid's Algorithm.
 *
 *   Euclid's algorithm divides one number by the other to obtain a remainder
 *   then continues to divide the divisor by the remainder until no remainder
 *   occurs. The resulting dividend is an even multiple of the divisor and is
 *   the greatest common divisor.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef GCD_SOURCE
#define GCD_SOURCE

#include "../calc/calc.h"

long gcd (register long x, register long y) 

{
	register long r;
	if ((x == 0) || (y == 0)) 
	{
		return (1);
	}
	while ((r = x % y)) 
	{
		x = y;
		y = r;
	}
	return (y);
}


#endif

