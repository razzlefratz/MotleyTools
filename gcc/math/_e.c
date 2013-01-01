/*====================================================================*
 *
 *   double _e();
 *
 *   _math.h
 *
 *   Compute the value of e (2.718282...) using the approximation series shown below.
 *   Terminate when two successive approximations are indistiguishable.
 *
 *   e = 1 + 1/1! + 1/2! + 1/3! + ...
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _E_SOURCE
#define _E_SOURCE

#include "../math/_math.h"

double _e () 

{
	register int term = 0;
	register double prod = 1;
	register double fact = 1;
	register double old = 0.0;
	register double sum;
	for (sum = 1; sum != old; sum += prod / fact) 
	{
		fact *= ++term;
		old = sum;
	}
	return (sum);
}


#endif

