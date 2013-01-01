/*====================================================================*
 *
 *   doubl _exp(double x);
 *
 *   _math.h
 *
 *   Compute the exponential value of a floating point number using the approximation series
 *   show below. Terminate when two successive approximations are indistinguishable.
 *
 *   _exp(x) = 1 + (x^1)/1! + (x^2)/2! + (x^3)/3! + ...
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _EXP_SOURCE
#define _EXP_SOURCE

#include "../math/_math.h"

double _exp (double x) 

{
	int term = 0;
	double prod = 1;
	double fact = 1;
	double old;
	double sum;
	for (sum = 1; sum != old; sum += prod/fact) 
	{
		prod *= x;
		fact *= ++term;
		old=sum;
	}
	return (sum);
}


#endif

