/*====================================================================*
 *
 *   bool strwcmp(char const *literal, char const *pattern, char const *wildcards);
 *
 *   strlib.h
 *
 *   this function performs wild_card string matching. Logical true is
 *   returned the string matches the specified format; otherwise, false
 *   is returned. Format string syntax is typical of common wild_card
 *   filename notations.
 *
 *   a mask character (mc) is used to denote the occurance of a single
 *   character and a wild character (wc) is used to denote an occurnace
 *   zero or more characters. All other characters specify a single
 *   occurance of the particular character. For example, strwcmp will
 *   return the illustrated values for:
 *
 *   true       = strwcmp("abc","???","?*");
 *   false      = strwcmp("abc","??","?*");
 *
 *   true       = strwcmp("abc","a*","?*");
 *   true       = strwcmp("abc","*c","?*");
 *   true       = strwcmp("abc","?b?","?*");
 *   false      = strwcmp("abc","b*","?*");
 *
 *   true       = strwcmp("abcccc","?b*","?*");
 *   true       = strwcmp("abbbbc","*b?","?*");
 *   true       = strwcmp("abbbbc","*c*","?*");
 *
 *   two versions are provided for academic interest only; the first
 *   is a recursive version; the second is not; we use the second to
 *   avoid consuming call stack space when matching unusual patterns
 *   or long literal strings;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRWCMP_SOURCE
#define STRWCMP_SOURCE

#include <ctype.h>

#include "../strlib/strlib.h"

#ifdef RECURSIVE

bool strwcmp (char const *literal, char const *pattern, char const *wildcards) 

{
	if (*pattern == (char)(0)) 
	{
		return (*literal == (char)(0));
	}
	else if (*pattern == wildcards [1]) 
	{
		for (++pattern; *literal; ++literal) 
		{
			if (strwcmp (literal, pattern, cp)) 
			{
				return (true);
			}
		}
		return (*pattern == (char)(0));
	}
	else if (*pattern == wildcards [0] || toupper (*pattern) == toupper (*literal)) 
	{
		return (strwcmp (++literal, ++pattern, cp));
	}
	else 
	{
		return (false);
	}
}


#else

bool strwcmp (char const *literal, char const *pattern, char const *wildcards) 

{
	register char const * cliteral = literal;
	register char const * cpattern = pattern;
	while (true) 
	{
		if (*cpattern == wildcards [1]) 
		{
			literal = cliteral;
			pattern = cpattern;
			cpattern++;
		}
		else if (toupper (*cliteral) == toupper (*cpattern)) 
		{
			if (*cpattern == (char)(0)) 
			{
				return (true);
			}
			else 
			{
				cliteral++;
				cpattern++;
			}
		}
		else if (*cliteral == (char)(0)) 
		{
			break;
		}
		else if (*cpattern == wildcards [0]) 
		{
			cliteral++;
			cpattern++;
		}
		else if (*pattern == wildcards [1]) 
		{
			cliteral = ++literal;
			cpattern = pattern + 1;
		}
		else 
		{
			break;
		}
	}
	return (false);
}


#endif

#endif

