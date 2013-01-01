/*====================================================================*
 *
 *   double _fmod(float x, float y);
 *
 *   _math.h
 *
 *   Compute the floating-point remainder of x/y.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _FMOD_SOURCE
#define _FMOD_SOURCE

#include "../math/_math.h"

double _fmod (double x, double y) 

{
	return (x - (long)(x / y) * y);
}


#endif

