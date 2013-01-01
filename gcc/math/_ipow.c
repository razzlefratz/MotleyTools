/*====================================================================*
 *
 *   long ipow(long x, signed y);
 *
 *   _math.h
 *
 *   return long integer value x raised to positive integer power y; 
 *   return 0 for negative integer powers; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _IPOW_SOURCE
#define _IPOW_SOURCE

#include "../math/_math.h"

long ipow (long x, signed y) 

{
	long n = 0;
	if (y >= 0) 
	{
		for (n = 1; y > 0; y >>= 1) 
		{
			if (y & 1) 
			{
				n *= x;
			}
			x *= x;
		}
	}
	return (n);
}


#endif

