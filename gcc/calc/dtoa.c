/*====================================================================*
 *
 *   ptrdiff_t dtoa(char *string, double value, int scale, int precision)
 *
 *   Convert a double precision floating point number to a string of
 *   given scale and precision; Return the string length; The scale
 *   is the magnitude as a power of ten; The precision limits the
 *   number of digits following the decimal point; A negative precision
 *   suppresses the decimal point, itself;
 *
 *   The number must be normalised such that -10.0 < number < 10.0.
 *   See dscale() for one method of normalizing the number.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stddef.h>
#include "../calc/calc.h"

ptrdiff_t dtoa (char *string, double value, int scale, int precision) 

{
	char *sp = string;
	if (value < 0.0) 
	{
		value = -value;
		*sp++ = '-';
	}
	while (scale >= 0) 
	{
		*sp++ = (char)((int)(value)+'0');
		value -= (int)(value);
		value *= 10.0;
		scale--;
	}
	if (precision > 0) 
	{
		for (*sp++ = '.'; (++scale < 0) && (precision-- > 0); *sp++ = '0');
		while (precision > 0) 
		{
			*sp++ = (char)((int)(value)+'0');
			value -= (int)(value);
			value *= 10.0;
			precision--;
		}
	}
	*sp = (char)(0);
	return (sp-string);
}

