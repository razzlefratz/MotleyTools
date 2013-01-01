/*====================================================================*
 *
 *   double _sin(double x);
 *
 *   _math.h
 *
 *   Compute the sine of a double precision value using the approximation series shown below.
 *   Terminate when two successive approximations are indistinguishable.
 *
 *   sin(x) = (x^1)/1! - (x^3)/3! + (x^5)/5! - (x^7)/7! + ...
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _SIN_SOURCE
#define _SIN_SOURCE

#include "../math/_math.h"

double _sin (double x) 

{
	register int term = 1;
	register int sign = 1;
	register double prod = x;
	register double fact = 1;
	register double old = 0.0;
	register double sum;
	for (sum = x; sum != old; sum += sign * prod / fact) 
	{
		prod *= x;
		prod *= x;
		fact *= ++term;
		fact *= ++term;
		sign = -sign;
		old = sum;
	}
	return (sum);
}


#endif

