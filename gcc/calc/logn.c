/*====================================================================*
 *
 *   double logn(double value, unsigned base);
 *
 *   calc.h
 *
 *   compute the log(10) of a double precision value; 
 *
 *   compute the exponent using successive division by 10; compute 
 *   the mantissa as the ratio of log(value) to log(10); compute the
 *   logarithm by adding the exponent and mantissa;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../calc/calc.h"

double logn (double value, unsigned base) 

{
	long exponent;
	double mantissa;
	if (value < 0) value = -value;
	for (exponent = 0; value >= base; exponent++) value /= base;
	mantissa = log (value) / log (base);
	return (exponent + mantissa);
}

