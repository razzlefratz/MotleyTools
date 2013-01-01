/*====================================================================*
 *
 *   void printn (unsigned long value, unsigned field, FILE *fp);
 *
 *   number.h
 *
 *   print an unsigned long integer value as a decimal string if fixed
 *   width or longer; pad left with '0' as needed;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef PRINTN_SOURCE
#define PRINTN_SOURCE

#include <stdio.h>

#include "../tools/number.h"

void printn (unsigned long value, unsigned field, FILE *fp) 

{
	if (field > 0) 
	{
		printn (value / 10, field - 1, fp);
		value %= 10;
		value += '0';
		putc (value, fp);
	}
	return;
}


#endif

