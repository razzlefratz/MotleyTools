/*====================================================================*
 *
 *   double _sqrt(double x);
 *
 *   _math.h
 *
 *   Compute square root of a double precision value. Return 0 for negative
 *   values of x.
 *
 *   The algorithm is a modified version of Newton's Method that uses an
 *   extra variable to detect repeating roots. The algorithm terminates when
 *   a repeating root occurs. This technique gets maximum precision
 *   based on the host machine wordsize.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _SQRT_SOURCE
#define _SQRT_SOURCE

#include "../math/_math.h"

double _sqrt (register double x) 

{
	register double root = 0;
	register double next = x;
	register double prev = x;
	if (x > 0) while ((root != next) && (root != prev)) 
	{
		prev = next;
		next = next + root;
		next = next / 2;
		root = x / next;
	}
	return (root);
}


#endif

