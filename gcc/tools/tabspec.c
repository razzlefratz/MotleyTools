/*====================================================================*
 *
 *   char * tabspec (char const * string);
 *
 *   tabs.h
 *
 *   This function parses a tab column specification string and inserts the
 *   appropriate tabstops using tabset(). It lets user specify many settings
 *   as one list. Individual settings are separated by commas, without
 *   intervening spaces.
 *
 *   A pointer to the remainder of the specification (or terminator) is
 *   returned. The terminator May (or May not) be a nul byte.
 *
 *   The general form of the specification is:
 *
 *   <tabspec> :== <setting>
 *   <tabspec> :== <tabspec>,<setting>
 *
 *   <setting> :== <column>
 *   <setting> :== <column>.<interval>
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef TABSPEC_SOURCE
#define TABSPEC_SOURCE

#include <stdlib.h>
#include <ctype.h>

#include "../tools/tabs.h"

char * tabspec(char const * string)

{
	char const * set;
	char const * tab;
	while (isdigit(* string))
	{
		for (set = string; isdigit(* string); string++);
		if (* string == '.')
		{
			string++;
		}
		for (tab = string; isdigit(* string); string++);
		if (* string == ',')
		{
			string++;
		}
		tabset (atoi(set), atoi(tab));
	}
	return ((char *) (string));
}

#endif



