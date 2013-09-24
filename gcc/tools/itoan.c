/*====================================================================*
 *
 *   char *itoan(unsigned long number, char buffer[], size_t length, char const *digits)
 *
 *   number.h
 *
 *   convert an integer to an unsigned numeric string of specified radix;
 *   and return the string address; the radix is specified by a string of
 *   digits starting with '0'; the radix is the string length;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ITOAN_SOURCE
#define ITOAN_SOURCE

#include "../tools/number.h"

char * itoan(unsigned long number, char buffer[], size_t length, register char const * digits)

{
	unsigned short radix;

#ifdef CMASSOC_SAFEMODE

	if (buffer == (char *)(0))
	{
		return (buffer);
	}
	if (digits == (char const *)(0))
	{
		return (buffer);
	}

#endif

	for (radix = 0; digits[radix]; radix++);
	if (length > 0)
	{
		buffer [-- length] = (char)(0);
		if (radix > 1)
		{
			do 
			{
				buffer [-- length] = digits[number % radix];
			}
			while (number /= radix);
		}
	}
	return (& buffer[length]);
}

#endif



