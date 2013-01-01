/*====================================================================*
 *
 *   long ipow(long x, int y);
 *
 *   calc.h
 *
 *   Compute the long integer value of a integer raised to a 
 *   positive integer power;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef IPOW_SOURCE
#define IPOW_SOURCE

#include "../calc/calc.h"

long ipow (int value, int power) 

{
	long product;
	for (product = 1; power > 0; power >>= 1) 
	{
		if (power & (unsigned) (1)) 
		{
			product *= value;
		}
		value *= value;
	}
	return (product);
}


#endif

