/*====================================================================*
 *
 *   long _sgn(long x);
 *
 *   _math.h
 *
 *   Return the sign of an integer value as either 1 or -1.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _SGN_SOURCE
#define _SGN_SOURCE

#include "../math/_math.h"

long _sgn (long x) 

{
	return ((x < 0)? (-1):(1));
}


#endif

