/*====================================================================*
 *
 *   unsigned strint(char const *string, char const *digits);
 *
 *   strlib.h
 *
 *   return the unsigned integer value of a numeric string; the digits
 *   string lists valid digits, starting with 0, for the desired radix;
 *   implicitly, the radix is the length of this string;
 *
 *   where "01" is binary, "01234567" is octal; "0123456789" is decimal,
 *   and "0123456789ABCDEF" is hexidecimal;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRINT_SOURCE
#define STRINT_SOURCE

#include <string.h>

#include "../strlib/strlib.h"
#include "../chrlib/chrlib.h"

unsigned long strint (char const *string, char const *digits) 

{
	unsigned short radix,
	digit;
	unsigned long value = 0;
	if (string) if (digits) 
	{
		if ((radix = strlen (digits)) > 1) 
		{
			while ((digit = chrindex (digits, *string++)) < radix) value = value * radix + digit;
		}
	}
	return (value);
}


#endif

