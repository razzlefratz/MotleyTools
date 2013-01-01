/*====================================================================*
 *
 *   int _abs(int x);
 *  
 *   _math.h
 *
 *   compute the absolute value of an integer:
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _ABS_SOURCE
#define _ABS_SOURCE

#include "../math/_math.h"

int _abs (int x) 

{
	return ((x < 0)? (-x):(x));
}


#endif

