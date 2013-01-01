/*====================================================================*
 *
 *   double _atof(char const *string);
 *
 *   conv.h
 *
 *   This function returns the real equivalent value of an ASCII string.
 *   With the exception of a single decimal point, evaluation terminates
 *   with the first non numeric character.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../stdlib/_stdlib.h"
#include "../string/_ctype.h"

double _atof (register char const *sp) 

{
	register double value = 0;
	register int power = 0;
	int minus = 0;
	if (sp) 
	{
		while (_isspace (*sp)) sp++;
		if (*sp == '+') 
		{
			sp++;
		}
		else if (*sp == '-') 
		{
			sp++;
			minus++;
		}
		while (_isdigit (*sp)) 
		{
			value = value * 10.0 + (*sp++ - '0');
		}
		if (*sp == '.') sp++;
		while (_isdigit (*sp)) 
		{
			value = value * 10.0 + (*sp++ -'0');
			power *= 10;
		}
	}
	return (((minus)? (-value):(value))/power);
}

