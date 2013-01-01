/*====================================================================*
 *
 *   char const *regexspan(const regexp *pattern, char const *literal);
 *
 *   regex.h
 *
 *   find the longest prefix of literal that satisfies the regular 
 *   expression; return a pointer to the remainder of literal when
 *   a match is found or (char *)(0) when not;
 *
 *   this function performs an anchored search where the start position
 *   is fixed but the end position moves looking for the longest match;
 *   the entire pattern must match but the entire string need not match 
 *   the pattern;
 *
 *   when pattern matches the entire string, the returned address will
 *   point to the NUL terminator; on return, the application can check
 *   for a NULL pointer then a NUL character to distinguish between no
 *   match, partial match or complete match;
 *
 *   char *string = regexspan (pattern, literal);
 *
 *   if (!string)
 *      printf("match failed!\n");
 *   else if (!*string)
 *      printf("all of the string matched the pattern.\n");
 *   else
 *      printf("part of string matched the pattern.\n");
 *
 *   use regexmake() to build a pattern from a string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef REGEXSPAN_SOURCE
#define REGEXSPAN_SOURCE

#include "../regex/regex.h"

char const *regexspan (const regexp * pattern, char const *literal) 

{
	char const *minimum;
	char const *maximum;
	char const *sp = (char const *)(0);
	if (!pattern) 
	{
		return (literal);
	}
	if (!literal) 
	{
		return (literal);
	}
	minimum = literal + pattern->minimum;
	maximum = literal + pattern->maximum;
	while (literal < maximum) 
	{
		if (!regexcomp (pattern->charset, *literal, pattern->exclude)) 
		{
			break;
		}

#if REGEX_TRACE

		printf ("-->[%s]\n", literal);

#endif

		literal++;
	}
	while (literal >= minimum) 
	{
		if ((sp = regexspan (pattern->next, literal))) 
		{
			break;
		}

#if REGEX_TRACE

		printf ("<--[%s]\n", literal);

#endif

		literal--;
	}

#if REGEX_TRACE

	printf ("---[%s]\n", literal);

#endif

	return (sp);
}


#endif

