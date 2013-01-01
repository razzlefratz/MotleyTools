/*====================================================================*
 *
 *   int dscale(double *value, int precision)
 *
 *   print.h
 *
 *   normalize a floating point number to the given precision and 
 *   return the magnitude as an integer power of ten; round to the 
 *   given number of decimal places before normalization when the 
 *   precision is positive;
 *
 *   normalization means "convert to a positive value less than ten":
 *
 *   this is a critical component of the print() function;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../tools/print.h"

#define _DSCALE 7

static double _pos [_DSCALE] = 

{
	1E+1,
	1E+2,
	1E+4,
	1E+8,
	1E+16,
	1E+32,
	1E+64
};

static double _neg [_DSCALE] = 

{
	1E-1,
	1E-2,
	1E-4,
	1E-8,
	1E-16,
	1E-32,
	1E-64
};

int dscale (double *number, int precision) 

{
	register signed int scale = 0;
	register unsigned range = _DSCALE;
	double value = (double)(*number);
	double round = (double)(5.0);
	int minus = 0;
	if (value < (double)(0.0)) 
	{
		value = -value;
		minus++;
	}
	if (precision >= 0) 
	{
		while (precision-- > 0) round /= (double)(10.0);
		value += round;
	}
	if (value >= (double)(10.0)) 
	{
		while (range-- > 0) 
		{
			scale <<= 1;
			if (value > _pos [range]) 
			{
				value *= _neg [range];
				scale++;
			}
		}
	}
	else if (value < (double)(1.0)) 
	{
		while (range-- > 0) 
		{
			scale <<= 1;
			if (value < _neg [range]) 
			{
				value *= _pos [range];
				scale--;
			}
		}
		value *= (double)(10.0);
		scale--;
	}
	*number = (minus)? -value: value;
	return (scale);
}

