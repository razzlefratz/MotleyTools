/*====================================================================*
 *
 *   bool match(char const *literal, char const *pattern);
 *
 *   tools.h
 *
 *   this function performs wildcard string matching. Logical true is
 *   returned if literal matches the specified pattern; pattern syntax
 *   is typical of common wildcard filename notations.
 *
 *   a mask character denotes the occurance of a single character and 
 *   a wild character denotes the occurnace zero or more characters. 
 *   other characters denote one occurance of themselves; For example, 
 *   match will return the illustrated values for:
 *
 *   true       = match("abc","???");
 *   false      = match("abc","??");
 *
 *   true       = match("abc","a*");
 *   true       = match("abc","*c");
 *   true       = match("abc","?b?");
 *   false      = match("abc","b*");
 *   true       = match("abc","*a*b*c*");
 *   true       = match("abc","a*********?");
 *
 *   true       = match("abcccc","?b*");
 *   true       = match("abbbbc","*b?");
 *   true       = match("abbbbc","*c*");
 *
 *   this function is the same as strwcmp() except that meta characters
 *   are fixed and comparisons are all character case sensitive here;
 *
 *   there are two versions included here; one is recursive; they should
 *   function identically;      
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MATCH_SOURCE
#define MATCH_SOURCE

#include "../tools/tools.h"

#define MATCH_C_MASK '?'
#define MATCH_C_WILD '*'

bool match (char const *literal, char const *pattern) 

#ifdef RECURSIVE


{
	if (*pattern == (char)(0)) 
	{
		return (*literal == (char)(0));
	}
	else if (*pattern == MATCH_C_WILD) 
	{
		for (++pattern; *literal; ++literal) 
		{
			if (match (literal, pattern)) 
			{
				return (true);
			}
		}

// return (match(literal, pattern));

		return (*pattern == (char)(0));
	}
	else if ((*pattern == MATCH_C_MASK) || (*pattern == *literal)) 
	{
		return (match (++literal, ++pattern));
	}
	else 
	{
		return (false);
	}
}


#else


{
	const register char *cliteral = literal;
	const register char *cpattern = pattern;
	while (true) 
	{
		if (*cpattern == MATCH_C_WILD) 
		{
			literal = cliteral;
			pattern = cpattern;
			cpattern++;
		}
		else if (*cliteral == *cpattern) 
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
		else if (*cpattern == MATCH_C_MASK) 
		{
			cliteral++;
			cpattern++;
		}
		else if (*pattern == MATCH_C_WILD) 
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

