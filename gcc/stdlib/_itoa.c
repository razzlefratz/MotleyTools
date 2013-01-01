/*====================================================================*
 *
 *   char *_itoa(char *string, signed value, unsigned short radix)
 *
 *   This function converts an integer to a signed numeric string having
 *   the specified radix and returns the string address; NULL is returned
 *   if the radix exceeds the range RADIX_MIN <= radix <= RADIX_MAX.
 *
 *   Octal and hexidecimal strings are not prefixed by either '0' or '0X'
 *   as in some other functions.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../stdlib/_stdlib.h"
#include "../string/_string.h"
#include "../chrlib/charset.h"

char *_itoa (char *string, register signed value, register unsigned short radix) 

{
	char *sp = string;
	int sign = 0;
	if (!string) 
	{
		return (string);
	}
	if ((radix < 2) || (radix > _strlen (gcsRadix))) 
	{
		return ((char *) (0));
	}
	if (value < 0) 
	{
		value = -value;
		sign--;
	}
	do 
	{
		*sp++ = gcsRadix [value % radix];
	}
	while (value /= radix);
	if (sign > 0) 
	{
		*sp++ = '+';
	}
	if (sign < 0) 
	{
		*sp++ = '-';
	}
	*sp = (char) (0);
	return ((char *) (_strrev (string)));
}

