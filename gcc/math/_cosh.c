/*====================================================================*
 *
 *   double _cosh(double x);
 *
 *   _math.h
 *
 *   Compute the hyperbolic cosine of a double precision vlue using the approximation series
 *   shown below. Terminate when two successive approximations are indistinguishable.
 *
 *   _cosh(x) = 1 + (x^2)/2! + (x^4)/4! + (x^6)/6! + ...
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _COSH_SOURCE
#define _COSH_SOURCE

#include "../math/_math.h"

double _cosh (register double x) 

{
	register int term = 0;
	register double prod = 1;
	register double fact = 1;
	register double old = 0.0;
	register double sum;
	for (sum = 1; sum != old; sum += prod /fact) 
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

