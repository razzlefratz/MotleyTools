/*====================================================================*
 *
 *   signed _atoi(char const *string);
 *
 *   _stdlib.h
 *
 *   this function returns the integer equivalent value of a character
 *   string; evaluation terminates with the first non-digit character;
 *   any null or non-numeric string, will return a value of zero; note
 *   that 'real' numeric strings, having a decimal point, will return
 *   the truncated integer value;
 *
 *   Copyright (1991) by Charles Maier Associates Ltd.;
 *
 *--------------------------------------------------------------------*/

#ifndef _ATOI_SOURCE
#define _ATOI_SOURCE

#include "../stdlib/_stdlib.h"
#include "../string/_ctype.h"

signed _atoi (register char const *string) 

{
	register signed value = 0;
	signed sign = 0;
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
			value *= 10;
			value += *string++ - '0';
		}
	}
	return ((sign)? (-value):(value));
}


#endif

