/*====================================================================*
 *
 *   double _atan(double x);
 *
 *   _math.h
 *
 *   Compute the arctangent a floating point number using one of the two the approximation
 *   series show below. Terminate when two successive approximations are indistinguishable.
 *
 *   atan(x) = (x^1)/1 - (x^3)/3 + (x^5)/5 - (x^7)/7 + ...
 *   atan(x) = pi/2 - 1/(1*x^1) + 1/(3*x^3) - 1/(5*x^5)) + 1/7*x^7 - ...
 *
 *   atan() converts the ratio of two sides of a right triangle to the corresponding angle
 *   in radians. The ratio is the length of the side opposite the angle to that of the side
 *   adjacent to the angle. The range of the result is -pi/2 to pi/2 radians.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _ATAN_SOURCE
#define _ATAN_SOURCE

#include "../math/_math.h"

/*
 * still needs some work 
 */

double _atan (double x) 

{
	int term;
	int sign;
	double prod;
	double fact;
	double old;
	double sum;
	if (x < 1) 
	{
		term = 1;
		prod = 1;
		fact = 1;
		old = 0;
		for (sum = x; sum != old; sum += sign * prod / fact) 
		{
			term++;
			term++;
			prod *= x;
			prod *= x;
			fact = term;
			sign = -sign;
			sum = old;
		}
		return (sum);
	}
	else if (x > 1) 
	{
		sign = -1;
		term = 1;
		prod = 1;
		fact = 1;
		old = 0;
		sum = PI/2;
		do 
		{
			old = sum;
			sum += sign / (prod * fact);
			term++;
			term++;
			prod *= x;
			prod *= x;
			fact = term;
			sign = -sign;
		}
		while (sum != old);
		return (sum);
	}
	else return (PI/4);
}


#endif

