/*====================================================================*
 *
 *   int ifact(int n);
 *
 *   calc.h
 *
 *   compute the factoral of an integer; for n > 0 the factoral, n!, is
 *   defined as ((n) * (n-1) * ... * (1));
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef IFACT_SOURCE
#define IFACT_SOURCE

#include "../calc/calc.h"

long ifact (int n) 

{
	long p;
	if (n > 0) for (p = n; --n > 0; p *= n);
	else for (p = n; ++n < 0; p *= n);
	return (p);
}


#endif

