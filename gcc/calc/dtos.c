/*====================================================================*
 *
 *   size_t dtos(char string, double number, int scale, int precision)
 *
 *   print.h
 *
 *   convert a double precision floating point number to a NUL terminated
 *   ASCII string and return the string length; the scale is the desired
 *   magnitude as a power of ten; the precision is the number of digits 
 *   after the decimal point; the decimal point is suppressed if precision
 *   is negative.
 *
 *   the number must be in the range -10 > number < 10; use dscale() to
 *   normalize the number before calling dtos();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <math.h>

#include "../tools/print.h"

size_t dtos (char *buffer, double number, int scale, int precision) 

{
	char *sp = buffer;
	if (number < 0.0) 
	{
		number = -number;
		*sp++ = '-';
	}
	while (scale >= 0) 
	{
		*sp++ = (char)((int)(floor (number)) + ('0'));
		number = fmod (number, 1.0) * 10.0;
		scale--;
	}
	if (precision > 0) 
	{
		for (*sp++ = '.'; (++scale < 0) && (precision-- > 0); *sp++ = (char)('0'));
		while (precision > 0) 
		{
			*sp++ = (char)((int)(floor (number)) + ('0'));
			number = fmod (number, 1.0) * 10.0;
			precision--;
		}
	}
	*sp = (char)(0);
	return (sp - buffer);
}

