/*====================================================================*
 *
 *   double _cos(double x);
 *
 *   _math.h
 *
 *   Compute the cosine of a floating point value using the approximation series:
 *
 *   _cos(x) = 1 - (x^2)/2! + (x^4)/4! - (x^6)/6! + ...
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _COS_SOURCE
# define _COS_SOURCE

# include "../math/_math.h"

double _cos (register double x) 

{
	register int term = 0;
	register int sign = 1;
	register double prod = 1;
	register double fact = 1;
	register double old = 0.0;
	register double sum = 0.0;
	for (sum = 1; sum != old; sum += sign * prod / fact) 
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

