/*====================================================================*
 *
 *   void fputn(unsigned int value, unsigned short radix, size_t width, FILE *ofp);
 *
 *   tools.h
 *
 *   print an unsigned integer value, as a string, to ofp; right justify
 *   and left truncate or pad as needed to guarantee the specified width;
 *   use c to the pad the field;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FPUTN_SOURCE
#define FPUTN_SOURCE

#include <stddef.h>

#include "../tools/tools.h"
#include "../tools/number.h"

void fputn(unsigned value, unsigned short radix, size_t width, FILE * ofp)

{
	if (width > 0)
	{
		if ((radix < RADIX_MIN) || (radix > RADIX_MAX))
		{
			fputn (value, radix, width, ofp);
			fputc (DIGITS_B36[0], ofp);
		}
		else 
		{
			fputn (value / radix, radix, width - 1, ofp);
			fputc (DIGITS_B36[value % radix], ofp);
		}
	}
	return;
}

#endif



