/*====================================================================*
 *
 *   char ** stov (char const * string);
 *
 *   convert a server query string to a string vector; applications
 *   must free the vector and associated string when done; * vector
 *   points to the associated string so don't lose it;
 *
 *   char ** vector = stov (getenv ("QUERY_STRING"));
 *   ...
 *   free (*vector);
 *   free (vector);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STOV_SOURCE
#define STOV_SOURCE

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../strlib/strlib.h"
#include "../tools/number.h"
#include "../tools/error.h"

char ** stov (char * string) 

{
	char *sp = string;
	char ** vector;
	char ** vp;
	signed item = 2;
	if (!string) 
	{
		string = "(empty)";
	}
	while (*sp) 
	{
		if (*sp++ == '&') 
		{
			item++;
		}
	}
	if (!(sp = malloc (strlen (string)))) 
	{
		error (1, errno, "Can't allocate string space");
	}
	if (!(vp = vector = malloc (item * sizeof (char *)))) 
	{
		error (1, errno, "Can't allocate vector space");
	}
	for (*vp++ = sp; *string; string++) 
	{
		if (*string == '&') 
		{
			if (item-- > 1) 
			{
				*vp++ = sp + 1;
				*sp++ = (char) (0);
			}
			continue;
		}
		if (*string == '%') 
		{
			unsigned value = 0;
			value += todigit (*++string);
			value *= 16;
			value += todigit (*++string);
			if (value >> 8) 
			{
				string--;
				string--;
				*sp++ = *string;
				continue;
			}
			*sp++ = value;
			continue;
		}
		if (*string == '+') 
		{
			*sp++ = ' ';
			continue;
		}
		*sp++ = *string;
	}
	*vp = (char *) (0);
	*sp = (char) (0);
	return (vector);
}


#endif

