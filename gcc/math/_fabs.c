/*====================================================================*
 *
 *   float _fabs(float x);
 *
 *   _math.h
 *
 *   Compute the absolute value of a floating point number.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _FABS_SOURCE
#define _FABS_SOURCE

#include "../math/_math.h"

float _fabs (float x) 

{
	return ((x < 0)? (-x):(x));
}


#endif

