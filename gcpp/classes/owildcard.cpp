/*====================================================================*
 *
 *   owildcard.cpp - implementation of the owildcard class.
 *
 *   this object implements wildcard pattern matching; wildcard pattern
 *   matching is easier to use than regular expression pattern matching
 *   because it has fewer options;
 *
 *   '?' means any single character in this pattern position;
 *   '*' means none or more characters in this pattern position;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oWILDCARD_SOURCE
#define oWILDCARD_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/owildcard.hpp"

/*====================================================================*
 *
 *   bool match(char const * literal, char const * pattern);
 *
 *   return true if the literal string argument matches the pattern string
 *   argument; the specific characters used as mask and wildcard are given 
 *   the charset string argument; the first is the mask; the second is the
 *   wildcard;
 *
 *--------------------------------------------------------------------*/

bool owildcard::match (char const * literal, char const * pattern) 

{

#ifdef oWILDCARD_RECURSIVE

	while (*literal) 
	{

// cerr << "[" << *literal << "] [" << *pattern << "]" << std::endl;

		if (*pattern == (char) (0)) 
		{
			return (false);
		}
		if (*pattern == this->allchar) 
		{
			for (++pattern; *literal != (char) (0); ++literal) 
			{
				if (this->match (literal, pattern)) 
				{
					return (true);
				}
			}
			break;
		}
		if (*pattern == this->anychar) 
		{
			pattern++;
			literal++;
			continue;
		}
		if (*pattern == *literal) 
		{
			pattern++;
			literal++;
			continue;
		}
		break;
	}
	return (*pattern == (char) (0));

#else

	const register char * cliteral = literal;
	const register char * cpattern = pattern;
	while (true) 
	{
		if (*cpattern == this->allchar) 
		{
			literal = cliteral;
			pattern = cpattern;
			cpattern++;
			continue;
		}
		if (*cliteral == *cpattern) 
		{
			if (*cpattern == (char) (0)) 
			{
				return (true);
			}
			cliteral++;
			cpattern++;
			continue;
		}
		if (*cliteral == (char) (0)) 
		{
			break;
		}
		if (*cpattern == this->anychar) 
		{
			cliteral++;
			cpattern++;
			continue;
		}
		if (*pattern == this->allchar) 
		{
			cliteral = ++literal;
			cpattern = pattern + 1;
			continue;
		}
		break;
	}
	return (false);

#endif

}


/*====================================================================*
 *
 *   owildcard ();
 *   
 *   initialize mask and wildcard characters with default values;
 *   
 *--------------------------------------------------------------------*/

owildcard::owildcard () 

{
	this->anychar = '?';
	this->allchar = '*';
	return;
}


/*====================================================================*
 *
 *   owildcard (unsigned char anychar, unsigned char allchar);
 *
 *   initialize default mask and wildcard characters with alternate
 *   values;
 *
 *--------------------------------------------------------------------*/

owildcard::owildcard (unsigned char anychar, unsigned char allchar) 

{
	this->anychar = (char) (anychar);
	this->allchar = (char) (allchar);
	return;
}


/*====================================================================*
 *
 *   ~owildcard();
 *
 *--------------------------------------------------------------------*/

owildcard::~owildcard () 

{
	return;
}


/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

