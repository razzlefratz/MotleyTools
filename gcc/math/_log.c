/*====================================================================*
 *
 *   double _log(double x);
 *
 *   _math.h
 *
 *   compute the natural log of a floating point number using the approximation series shown
 *   below. Terminate when two successive approximations are indistinguishable.
 *
 *   _log(x) = (x-1)/(x+1) + (1/3)((x-1)/(x+1))^3 + (1/5)((x-1)/(x+1))^5 + ...
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _LOG_SOURCE
#define _LOG_SOURCE

#include "../math/_math.h"

double _log (register double x) 

{
	register int term = 0;
	register double prod = 0.0;
	register double fact = 0.0;
	register double old = 0.0;
	register double sum = 0.0;
	if (x > 0) 
	{
		x = (x-1)/(x+1);
		term = 1;
		prod = x;
		for (sum = x; sum != old; sum += prod / fact) 
		{
			term++;
			term++;
			prod *= x;
			prod *= x;
			fact = term;
			old = sum;
		}
		return (sum * 2);
	}
	return (0);
}


#endif

