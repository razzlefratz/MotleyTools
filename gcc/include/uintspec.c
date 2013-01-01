/*====================================================================*
 *
 *   unsigned uintspec (char const *string, unsigned minimum, unsigned maximum);
 *
 *   tools.h
 *
 *   convert a numeric string to a positive integer value; return
 *   the default value if the string is void or the value exceeds
 *   the specified range;
 *
 *   unlike atoi(), string must contain at least one decimal digit
 *   and then only decimal digits; otherwise, the default value is 
 *   returned; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef UINTSPEC_SOURCE
#define UINTSPEC_SOURCE

#include <ctype.h>
#include <errno.h>

#include "../tools/tools.h"
#include "../tools/error.h"

unsigned uintspec (char const *string, unsigned minimum, unsigned maximum) 

{
	unsigned integer = 0;
	char const *sp;

#ifdef CMASSOC_SAFEMODE

	if ((string == (char *) (0)) || (*string == (char)(0))) 
	{
		error (1, ENODATA, "operand is null or empty");
	}

#endif

	for (sp = string; isdigit (*sp); integer = (integer * 10) + (*sp++ - '0'));
	if (*sp != (char) (0)) 
	{
		error (1, 0, "operand %s is not an unsigned integer", string);
	}
	if ((integer < minimum) || (integer > maximum)) 
	{
		error (1, 0, "operand %s exceeds range %d to %d", string, minimum, maximum);
	}
	return (integer);
}


#endif

