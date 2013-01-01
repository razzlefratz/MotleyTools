/*====================================================================*
 *
 *   unsigned month (char const *string);
 *
 *.  Motley Tools by Charles Maier
 *;  Licensed under the Internet Software Consortium License
 *:  Published 1982-2005 by Charles Maier for personal use
 *
 *--------------------------------------------------------------------*/

#include <string.h>

#include "../date/date.h"

unsigned month (char const *string) 

{
	extern char const *sv_month [];
	unsigned index;
	for (index = 0; index < 12; index++) 
	{
		if (strcmp (string, sv_month [index]) == 0) 
		{
			return (index + 1);
		}
	}
	return (0);
}

