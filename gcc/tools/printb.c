/*====================================================================*
 *
 *   void printb (unsigned value, unsigned field, unsigned group, FILE *fp);
 *
 *   number.h
 *
 *   print an unsigned value as a binary field of the specified width;
 *   group bits into subfields of specified width separated by a space;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef PRINTB_SOURCE
#define PRINTB_SOURCE

#include <stdio.h>

#include "../tools/number.h"

void printb(unsigned value, unsigned field, unsigned group, FILE * fp)

{
	if (field > 0)
	{
		printb (value >> 1, field - 1, group, fp);
		if (group > 0)
		{
			if ((field % group) == 0)
			{
				putc (' ', fp);
			}
		}
		value &= 0x01;
		value += '0';
		putc (value, fp);
	}
	return;
}

#endif



