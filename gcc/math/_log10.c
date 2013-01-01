/*====================================================================*
 *
 *   double _log10(double value);
 *
 *   _math.h
 *
 *   compute the base 10 logarithm of a double precision value; the 
 *   exponent is computed by successive division by 10; the mantissa  
 *   by the ratio of log(value) to log(10); the sum of the exponent 
 *   and mantissa is returned as the function value;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _LOG10_SOURCE
#define _LOG10_SOURCE

#ifndef _LOG10_SOURCE
#define _LOG10_SOURCE

#include "../math/_math.h"

double _log10 (double value) 

{
	long exponent;
	double mantissa;
	if (value < 0) 
	{
		value = -value;
	}
	for (exponent = 0; value >= 10; exponent++) 
	{
		value /= 10;
	}
	mantissa = _log (value) / _log (10);
	return (exponent + mantissa);
}


#endif

#endif

