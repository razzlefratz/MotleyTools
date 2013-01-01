/*====================================================================*
 *
 *   bool regexcomp(char const *charset, char character, bool exclude);
 *
 *   determine if a character belongs to a character set; a character
 *   set is specified as a string that contains all characters in the 
 *   set unless the exclude flag is set true; in that case the string
 *   contains all characters not in the set; 
 *
 *   the set of all characters is specified with an empty string plus 
 *   the exclude flag set true; the set of not characters is the same
 *   with the exclude flag set false;
 *
 *   the NUL character returns false regardless of string content and
 *   exclude flag state; it cannot belong to any character set;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef REGEXCOMP_SOURCE
#define REGEXCOMP_SOURCE

#include "../regex/regex.h"

bool regexcomp (char const *charset, char character, bool exclude) 

{
	if ((!charset) || (!character)) 
	{
		return (false);
	}
	while (*charset) 
	{
		if (*charset++ == character) 
		{
			return (!exclude);
		}
	}
	return (exclude);
}


/*====================================================================*
 *   dmo/test program;
 *--------------------------------------------------------------------*/

#if 0

int main (int argc, char const * argv []) 

{
	char const * charset;
	char const * literal;
	if (*++argv) 
	{
		charset = *argv;
	}
	while (*++argv) 
	{
		literal = *argv;
		while (*literal) 
		{
			bool match = regexcomp (charset, *literal, false);
			printf ("%c %s [%s]\n", *literal, match? "in": "not in", charset);
			literal++;
		}
	}
	return (0);
}


#endif

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

