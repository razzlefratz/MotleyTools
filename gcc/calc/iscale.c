/*====================================================================*
 *
 *   int iscale(long int value);
 *
 *   print.h
 *
 *   return the integer log(10) of a long integer value;
 *
 *   array _scale[] contains long integer values used to calculate the
 *   integer log(10) of a number; each array element is the square of
 *   the previous element, starting with 10.
 *
 *   the largest element should not exceed the sizeof 'long int' on the
 *   host machine; _ISCALE is the array size;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../calc/calc.h"
#include "../tools/print.h"

#define _ISCALE 4

int iscale (long int value) 

{
	static long int _scale [_ISCALE] = 
	{
		10,
		100,
		10000,
		100000000,
	};
	unsigned scale;
	unsigned range;
	range = _ISCALE;
	scale = 0;
	if (value < 0) value = -value;
	while (range-- > 0) 
	{
		scale <<= 1;
		if (value >= _scale [range]) 
		{
			value /= _scale [range];
			scale++;
		}
	}
	return (scale);
}

