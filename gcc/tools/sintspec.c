/*====================================================================*
 *
 *   signed long long sintspec (char const * string, signed long long number);
 *
 *   tools.h
 *
 *   adjust a number by the value specified in string; string may
 *   start with '=', '+' or '-' to indicate an operation where the 
 *   default operation is '='; the remainder of string specifies an
 *   integer value that will be assigned to, added to, subtracted 
 *   from number; the result is returned on success; on error, the
 *   global variable errno is set to EINVAL and 0 is returned;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SINTSPEC_SOURCE
#define SINTSPEC_SOURCE

#include <stdint.h>
#include <errno.h>
#include <ctype.h>

#include "../tools/number.h"
#include "../tools/error.h"

signed long long sintspec (char const * string, signed long long number) 

{
	signed sign = 0;
	signed long long offset = 0;
	if (!string) 
	{
		error (1, EINVAL, __func__);
	}
	if (*string == '=') 
	{
		string++;
	}
	else if (*string == '+') 
	{
		string++;
		sign++;
	}
	else if (*string == '-') 
	{
		string++;
		sign--;
	}
	while (isdigit (*string)) 
	{
		offset *= 10;
		offset += *string++ - '0';
	}
	if (*string) 
	{
		errno = EINVAL;
		number = 0;
	}
	else if (sign > 0) 
	{
		number += offset;
	}
	else if (sign < 0) 
	{
		number -= offset;
	}
	else 
	{
		number = offset;
	}
	return (number);
}


#endif

