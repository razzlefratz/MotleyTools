/*====================================================================*
 *
 *   double _sinh(double x);
 *
 *   _math.h
 *
 *   Compute the hyberbolic sine of a floating point value using the approximation series:
 *
 *   sinh(x) = (x^1)/1! + (x^3)/3! + (x^5)/5! + (x^7)/7! + ...
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _SINH_SOURCE
#define _SINH_SOURCE

#include "../math/_math.h"

double _sinh (register double x) 

{
	register int term = 1;
	register double prod = x;
	register double fact = 1;
	register double old = 0.0;
	register double sum;
	for (sum = x; sum != old; sum += prod / fact) 
	{
		prod *= x;
		prod *= x;
		fact *= ++term;
		fact *= ++term;
		old = sum;
	}
	return (sum);
}


#endif

