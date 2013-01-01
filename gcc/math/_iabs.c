/*====================================================================*
 *
 *   int _iabs(int x);
 *
 *   _math.h
 *
 *   Compute the absolute value of an integer:
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _IABS_SOURCE
#define _IABS_SOURCE

#include "../math/_math.h"

int _iabs (int x) 

{
	return ((x < 0)? (-x):(x));
}


#endif

