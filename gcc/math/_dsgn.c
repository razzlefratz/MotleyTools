/*====================================================================*
 *
 *   double _dsgn(double x);
 *
 *   _math.h
 *
 *   Compute the sign of a floating point number and return either 1 or -1.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _DSGN_SOURCE
#define _DSGN_SOURCE

#include "../math/_math.h"

double _dsgn (double x) 

{
	return ((x < 0)? (-1):(1));
}


#endif

