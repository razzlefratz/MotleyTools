/*====================================================================*
 *
 *   double _dmod(double x, double y);
 *
 *   _math.h
 *
 *   Compute the double precision remainder of x/y.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _DMOD_SOURCE
#define _DMOD_SOURCE

#include "../math/_math.h"

double _dmod (double x, double y) 

{
	return (x - (long)(x / y) * y);
}


#endif

