/*====================================================================*
 *
 *   void printx (unsigned value, unsigned field, FILE *fp);
 *
 *   number.h
 *
 *   recursively print an unsigned integer on stdout in hexadeximal
 *   format;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef PRINTX_SOURCE
#define PRINTX_SOURCE

#include <stdio.h>

#include "../tools/number.h"

void printx (unsigned value, unsigned field, FILE *fp) 

{
	if (field > 0) 
	{
		printx (value >> 4, field - 1, fp);
		putc (DIGITS_HEX [value & 0x0F], fp);
		return;
	}
	return;
}


#endif

