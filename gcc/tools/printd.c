/*====================================================================*
 *
 *   void printd (signed value, FILE *fp);
 *
 *   number.h
 *
 *   recursively print a signed integer value on stdout in decimal
 *   format;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef PRINTD_SOURCE
#define PRINTD_SOURCE

#include <stdio.h>

#include "../tools/number.h"

void printd (unsigned value, FILE * fp) 

{
	if (value > 9) 
	{
		printd (value / 10, fp);
	}
	value %= 10;
	value += '0';
	putc (value, fp);
	return;
}


#endif

