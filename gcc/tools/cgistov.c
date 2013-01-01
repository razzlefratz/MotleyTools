/*====================================================================*
 *
 *   char const ** cgistov (char * string);
 *
 *   convert a server query string to a string vector; applications 
 *   must free the vector and associated string when done; *vector 
 *   points to the start of string;
 *
 *   char ** vector = cgistov (getenv ("QUERY_STRING"));
 *   ...
 *   free (*vector);
 *   free (vector);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CGISTOV_SOURCE
#define CGISTOV_SOURCE

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../tools/error.h"

char const ** cgistov (char * string) 

{
	char ** vector;
	char ** vp;
	char * sp;
	signed item = 2;
	if (!string) 
	{
		string = "";
	}
	for (sp = string; *sp; sp++) 
	{
		if (*sp == '&') 
		{
			item++;
		}
	}
	if (!(sp = malloc (strlen (string) + 1))) 
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
			unsigned ascii = 0;
			ascii += todigit (*++string);
			ascii *= 16;
			ascii += todigit (*++string);
			if (ascii >> 8) 
			{
				string--;
				string--;
				*sp++ = *string;
				continue;
			}
			*sp++ = ascii;
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
	return ((char const **)(vector));
}


#endif

