/*====================================================================*
 *
 *   char const *regexmin(const regexp *pattern, char const *literal);
 *
 *   regex.h
 *
 *   find the shortest prefix of literal that can be described by the 
 *   regular expression in pattern; return a pointer to the remainder 
 *   of the string if a match occurs; return NULL if not;
 *
 *   this function performs an anchored search; this means that the start
 *   position is fixed but the end position moves looking for the longest
 *   match; the entire pattern must be matched to succeed but the entire
 *   string need not match the pattern;
 *
 *   if a pattern describes the entire string then the returned address
 *   points to the NUL terminator; on return, the application can check
 *   the pointer for NULL to detect a match then check the character to
 *   detect a complete match;
 *
 *   char *sp = regexspan(pattern, literal);
 *
 *   if (sp == NULL)
 *      printf("match failed!\n");
 *   else if (*sp == NUL)
 *      printf("all of the string matched the pattern.\n");
 *   else
 *      printf("part of string matched the pattern.\n");
 *
 *   pattern structures are built from string expressions by regexdef()
 *   and iused to accelerate the detection of patterns in other strings;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef REGEXMIN_SOURCE
#define REGEXMIN_SOURCE

#include "../regex/regex.h"

char const *regexmin (const regexp *pattern, char const *literal) 

{
	char const *minimum;
	char const *maximum;
	char const *sp = (char *)(0);
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
	while (literal < minimum) 
	{
		if (!regexcomp (pattern->charset, *literal, pattern->exclude)) 
		{
			return (sp);
		}
		literal++;
	}
	while (literal <= maximum) 
	{
		if ((sp = regexmin (pattern->next, literal))) 
		{
			return (sp);
		}
		literal++;
	}
	return (sp);
}


#endif

