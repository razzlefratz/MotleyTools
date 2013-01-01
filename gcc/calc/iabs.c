/*====================================================================*
 *
 *   int iabs(int x);
 *
 *   calc.h
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

#include "../calc/calc.h"

int iabs (int x) 

{
	return ((x < 0)? (-x):(x));
}

