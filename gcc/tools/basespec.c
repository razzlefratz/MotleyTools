/*====================================================================*
 *
 *   unsigned long basespec (char const * string, unsigned base, unsigned size);
 *
 *   number.h
 *
 *   convert a numeric string to an unsigned integer of the specified
 *   size in bytes; the base can be 0, 2, 10 or 16 where base 0 means
 *   the value may be binary, decimal or hexadecimal based on prefix;
 *   binary values start with "0b" and hexadecimal values with "0x";
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef BASESPEC_SOURCE
#define BASESPEC_SOURCE

#include <stdlib.h>
#include <ctype.h>

#include "../tools/number.h"
#include "../tools/error.h"

unsigned long basespec(char const * string, unsigned base, unsigned size)

{
	char const * number = string;
	unsigned radix = 10;
	unsigned long value = 0;
	unsigned long limit = 0;
	unsigned digit = 0;
	signed factor = 1;
	limit = ~ limit;
	if (size < sizeof(limit))
	{
		limit <<= size << 3;
		limit = ~ limit;
	}
	if (! number)
	{
		error (1, EINVAL, __func__);
	}
	while (isspace(* number))
	{
		number++;
	}
	if (base)
	{
		radix = base;
	}
	else 
	{
		base = radix;
	}
	if (* number == '=')
	{
		number++;
	}
	else if(* number == '+')
	{
		number++;
	}
	else if(* number == '-')
	{
		factor = - 1;
		number++;
	}
	if (* number == '0')
	{
		number++;
		if ((* number == 'b') || (* number == 'B'))
		{
			radix = 2;
			number++;
		}
		else if((* number == 'd') || (* number == 'D'))
		{
			radix = 10;
			number++;
		}
		else if((* number == 'x') || (* number == 'X'))
		{
			radix = 16;
			number++;
		}
	}
	if (base != radix)
	{
		error (1, EINVAL, "Have %s but need base %d value", string, base);
	}
	while ((digit = todigit(* number)) < radix)
	{
		value *= radix;
		value += digit;
		if (value > limit)
		{
			error (1, ERANGE, "Have %s but need %d bit value", string, (size << 3));
		}
		number++;
	}
	while (isspace(* number))
	{
		number++;
	}
	if (* number)
	{
		error (1, EINVAL, "Have %s but need base %d value", string, base);
	}
	return (value);
}

#endif



