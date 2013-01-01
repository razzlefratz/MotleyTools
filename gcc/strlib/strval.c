/*====================================================================*
 *
 *   int strval(char const *string, char const *digits, unsigned count, unsigned *value);
 *
 *   attempt to compute the unsigned value of a fixed width integer
 *   field and update the referenced unsigned integer value; return
 *   1 if successful and 0 if not;
 *
 *   success means the specified number of digits were found and that
 *   the result is valid; failure means too few digits were found and
 *   the result should be ignored;
 *
 *   for example:
 *
 *   unsigned value = 0;
 *   if (strval(&"ab%20cd"[3], "0123456789ABCDEF", 2, &value))
 *   {
 *      .... <value is valid>
 *   }
 *
 *   we asked strval() to parse 2 hex digits starting at offset 3 in
 *   the hex encoded string; it returned 1 because 2 hex digits were
 *   found and so value contains 0x20 or 32 or SP, as you prefer;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   compiled using gnu gcc compiler under debian linus;
 *
 *--------------------------------------------------------------------*/

#ifndef STRVAL_SOURCE
#define STRVAL_SOURCE

#include <string.h>

#include "../strlib/strlib.h"

int strval (char const *string, char const *digits, unsigned count, unsigned *value) 

{
	char *digit;
	if (count == 0) 
	{
		return (1);
	}
	else if ((digit = strchr (digits, *string)) == (char *)(0)) 
	{
		return (0);
	}
	else 
	{
		*value *= strlen (digits);
		*value += digit - digits;
		return (strval (string + 1, digits, count - 1, value));
	}
}


#endif

