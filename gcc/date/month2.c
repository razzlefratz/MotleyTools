/*====================================================================*
 *
 *   unsigned month2 (char const *string);
 *
 *   return the month number for the month name;
 *
 *.  Motley Tools by Charles Maier
 *;  Licensed under the Internet Software Consortium License
 *:  Published 1982-2005 by Charles Maier for personal use
 *
 *--------------------------------------------------------------------*/

#ifndef MONTH2_SOURCE
#define MONTH2_SOURCE

#include <string.h>

#include "../date/date.h"

unsigned month2 (char const *string) 

{
	extern char const *sv_month [];
	char const *sp;
	char const *cp;
	unsigned index;
	for (index = 0; index < 12; index++) 
	{
		sp = string;
		cp = sv_month [index];
		while ((*sp != (char) (0)) && (*cp != (char) (0)) && (*sp == *cp)) 
		{
			sp++;
			cp++;
		}
		if ((sp - string) > 2) 
		{
			if ((*sp == (char) (0)) || (*cp == (char) (0))) 
			{
				return (index + 1);
			}
		}
	}
	return (0);
}


#endif

