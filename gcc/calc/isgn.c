/*====================================================================*
 *
 *   int isgn(int x);
 *
 *   calc.h
 *
 *   compute the sign of a long integer and return as either -1 or 1;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../calc/calc.h"

long isgn (long x) 

{
	return ((x < 0)? (-1):(1));
}

