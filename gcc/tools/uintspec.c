/*====================================================================*
 *
 *   unsigned long long uintspec (char const * string, unsigned long long minimum, unsigned long long maximum);
 *
 *   number.h
 *
 *   convert a numeric string to an unsigned integer; confirm that
 *   the result does not exceed the specified range; report errors 
 *   and terminate the program on error;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef UINTSPEC_SOURCE
#define UINTSPEC_SOURCE

#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

#include "../tools/number.h"
#include "../tools/error.h"

unsigned long long uintspec (char const * string, unsigned long long minimum, unsigned long long maximum) 

{
	char const * number = string;
	unsigned radix = 10;
	unsigned long long value = 0;
	unsigned digit;
	if (!number) 
	{
		error (1, EINVAL, __func__);
	}
	while (isspace (*number)) 
	{
		number++;
	}
	if (*number == '0') 
	{
		number++;
		if ((*number == 'b') || (*number == 'B')) 
		{
			radix = 2;
			number++;
		}
		else if ((*number == 'd') || (*number == 'D')) 
		{
			radix = 10;
			number++;
		}
		else if ((*number == 'x') || (*number == 'X')) 
		{
			radix = 16;
			number++;
		}
	}
	while ((digit = todigit (*number)) < radix) 
	{
		value *= radix;
		value += digit;
		number++;
	}
	while (isspace (*number)) 
	{
		number++;
	}
	if (*number) 
	{
		error (1, EINVAL, "Have '%s' but need unsigned integer", string);
	}
	if ((value < minimum) || (value > maximum)) 
	{

#ifdef WIN32 

		error (1, ERANGE, "Have '%s' but need '%I64d' thru '%I64d'", string, minimum, maximum);

#else

		error (1, ERANGE, "Have '%s' but need '%llu' thru '%llu'", string, minimum, maximum);

#endif

	}
	return (value);
}


#endif

