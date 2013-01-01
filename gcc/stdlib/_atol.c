/*====================================================================*
 *
 *   signed long _atol(char const *string);
 *
 *   _stdlib.h
 *
 *   this function returns the integer equivalent value of a character
 *   string; evaluation terminates with the first non-digit character;
 *   any null or non-numeric string, will return a value of zero; note
 *   that 'real' numeric strings, having a decimal point, will return
 *   the truncated integer value;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../stdlib/_stdlib.h"
#include "../stdlib/_stddef.h"
#include "../string/_ctype.h"

signed long _atol (register char const *string) 

{
	register signed long value = 0;
	int sign = 0;
	if (string) 
	{
		while (_isspace (*string)) 
		{
			string++;
		}
		if (*string == '+') 
		{
			string++;
		}
		else if (*string == '-') 
		{
			string++;
			sign--;
		}
		while (_isdigit (*string)) 
		{
			value = value * 10 + (*string++ - '0');
		}
	}
	return ((sign)? (-value):(value));
}

