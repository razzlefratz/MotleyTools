/*====================================================================*
 *
 *   unsigned long atoin (char const *string, char const *digits);
 *
 *   number.h
 *
 *   return the unsigned integer value of a numeric string in any number
 *   base; the base is implicitly specified by the NUL terminated digits
 *   string containing all valid digits for the base, starting from '0';
 *
 *   for example, "0123456789ABCDEF" has 16 characters and so 16 is the
 *   number base;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ATOIN_SOURCE
#define ATOIN_SOURCE

#include "../tools/number.h"

unsigned long atoin(char const * string, char const * digits)

{
	unsigned short radix;
	unsigned short digit;
	unsigned long value = 0;

#ifdef CMASSOC_SAFEMODE

	if (string == (char const *)(0))
	{
		return (0);
	}
	if (digits == (char const *)(0))
	{
		return (0);
	}

#endif

	for (radix = 0; digits[radix]; radix++);
	while (* string)
	{
		for (digit = 0; digit < radix; digit++)
		{
			if (* string++ == digits[digit])
			{
				value *= radix;
				value += digit;
				break;
			}
		}
		if (digit == radix)
		{
			return (0);
		}
	}
	return (value);
}

#endif



