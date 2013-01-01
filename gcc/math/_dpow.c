/*====================================================================*
 *
 *   double _dpow(double x, signed y);
 *
 *   _math.h
 *
 *   return double precision value x raised to integer power y;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _DPOW_SOURCE
#define _DPOW_SOURCE

#include "../math/_math.h"

double _dpow (double x, signed y) 

{
	double n = 1;
	signed m = 1;
	if (y < 0) 
	{
		y = -y;
		m = -m;
	}
	for (n = 1; y > 0; y >>= 1) 
	{
		if (y & 1) 
		{
			if (m > 0) 
			{
				n *= x;
			}
			if (m < 0) 
			{
				n /= x;
			}
		}
		x *= x;
	}
	return (n);
}


#endif

