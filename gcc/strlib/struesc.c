/*====================================================================*
 *
 *   char *struesc(char *string);
 *
 *   strlib.h
 *
 *   scan a string for character escape sequences of the form '\ddd', '\c',
 *   and '^c'; replace each sequence with the corresponding character value;
 *   return the string argument as the function value;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRUESC_SOURCE
#define STRUESC_SOURCE

#include <ctype.h>
#include <limits.h>

#include "../strlib/strlib.h"
#include "../chrlib/chrlib.h"
#include "../tools/number.h"

char *struesc (register char *string) 

{
	register char *sp;
	register char *cp;
	if (string) for (sp = cp = string; (*sp = *cp++); ++sp) 
	{
		if (*sp == '\\') 
		{
			if (isoctal (*cp)) 
			{
				*sp = todigit (*cp++);
				if (isoctal (*cp)) 
				{
					*sp *= 8;
					*sp += todigit (*cp++);
				}
				if (isoctal (*cp)) 
				{
					*sp *= 8;
					*sp += todigit (*cp++);
				}
				continue;
			}
			if ((*cp == 'x') || (*cp == 'X')) 
			{
				*sp = 0;
				cp++;
				if (isxdigit (*cp)) 
				{
					*sp *= 16;
					*sp += todigit (*cp++);
				}
				if (isxdigit (*cp)) 
				{
					*sp *= 16;
					*sp += todigit (*cp++);
				}
				continue;
			}

#ifdef STRUESC_STANDALONE

			if (*cp == 'a') 
			{
				*sp = '\a';
			}
			else if (*cp == 'b') 
			{
				*sp = '\b';
			}
			else if (*cp == 'f') 
			{
				*sp = '\f';
			}
			else if (*cp == 'n') 
			{
				*sp = '\n';
			}
			else if (*cp == 'r') 
			{
				*sp = '\r';
			}
			else if (*cp == 't') 
			{
				*sp = '\t';
			}
			else if (*cp == 'v') 
			{
				*sp = '\v';
			}
			else if (*cp == '?') 
			{
				*sp = '\?';
			}
			else if (*cp == '\'') 
			{
				*sp = '\'';
			}
			else if (*cp == '\"') 
			{
				*sp = '\"';
			}
			else if (*cp == '\\') 
			{
				*sp = '\\';
			}
			else 
			{
				*sp = *cp;
			}
			cp++;

#else

			*sp = chruesc (*cp++);

#endif

			continue;
		}

#ifdef CHRLIB_ISO_646_1983

		if ((*sp == '?') && (*cp == '?')) 
		{
			cp++;
			if (*cp == '=') 
			{
				*sp = '#';
			}
			else if (*cp == '(') 
			{
				*sp = '[';
			}
			else if (*cp == '/') 
			{
				*sp = '\\';
			}
			else if (*cp == ')') 
			{
				*sp = ']';
			}
			else if (*cp == '\'') 
			{
				*sp = '^';
			}
			else if (*cp == '<') 
			{
				*sp = '{';
			}
			else if (*cp == '!') 
			{
				*sp = '|';
			}
			else if (*cp == '>') 
			{
				*sp = '}';
			}
			else if (*cp == '-') 
			{
				*sp = '~';
			}
			else 
			{
				cp--;
				continue;
			}
			cp++;
			continue;
		}

#endif

		if (*sp == '^') 
		{
			*sp = *cp++ & 0x1F;
			continue;
		}
	}
	return (string);
}


#endif

