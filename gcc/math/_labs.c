/*====================================================================*
 *
 *   long _labs(long x);
 *
 *   _math.h
 *
 *   Compute the absolute value of a long integer:
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _LABS_SOURCE
#define _LABS_SOURCE

#include "../math/_math.h"

long _labs (long x) 

{
	return ((x < 0)? (-x):(x));
}


#endif

