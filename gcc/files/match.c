/*====================================================================*
 *
 *   bool match(char const *filename, char const *wildcard);
 *
 *   basic.h
 *
 *   this function performs wildcard string matching. Logical true is
 *   returned if filename matches the specified wildcard; wildcard syntax
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

#include "../files/files.h"

#ifndef MATCH_C_MASK
#define MATCH_C_MASK '?'
#endif

#ifndef MATCH_C_WILD
#define MATCH_C_WILD '*'
#endif

bool match (char const *filename, char const *wildcard) 

#ifdef RECURSIVE


{
	if (*wildcard == (char)(0)) 
	{
		return (*filename == (char)(0));
	}
	else if (*wildcard == MATCH_C_WILD) 
	{
		for (++wildcard; *filename; ++filename) 
		{
			if (match (filename, wildcard)) 
			{
				return (true);
			}
		}

// return (match(filename, wildcard));

		return (*wildcard == (char)(0));
	}
	else if ((*wildcard == MATCH_C_MASK) || (*wildcard == *filename)) 
	{
		return (match (++filename, ++wildcard));
	}
	else 
	{
		return (false);
	}
}


#else


{
	register char const * cfilename = filename;
	register char const * cwildcard = wildcard;
	while (true) 
	{
		if (*cwildcard == MATCH_C_WILD) 
		{
			filename = cfilename;
			wildcard = cwildcard;
			cwildcard++;
		}
		else if (*cfilename == *cwildcard) 
		{
			if (*cwildcard == (char)(0)) 
			{
				return (true);
			}
			else 
			{
				cfilename++;
				cwildcard++;
			}
		}
		else if (*cfilename == (char)(0)) 
		{
			break;
		}
		else if (*cwildcard == MATCH_C_MASK) 
		{
			cfilename++;
			cwildcard++;
		}
		else if (*wildcard == MATCH_C_WILD) 
		{
			cfilename = ++filename;
			cwildcard = wildcard + 1;
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

