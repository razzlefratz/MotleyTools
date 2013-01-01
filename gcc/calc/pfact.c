/*====================================================================*
 *
 *   long pfact(int x, int y);
 *
 *   calc.h
 *
 *   compute the partial factoral of two integers; for 0 < y < x the
 *   partial factoral x!/y! is defined as ((x) * (x-1) * ... * (y+1));
 *   if y = 0 then the factoral is x!; if y = x the factorial is 1;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef PFACT_SOURCE
#define PFACT_SOURCE

#include "../calc/calc.h"

long pfact (register int x, register int y) 

{
	register long p = 1;
	if (y < 0) y = 0;
	while (x > y) p *= x--;
	return (p);
}


#endif

