/*====================================================================*
 *
 *   regexp *regexmake(char const *string);
 *
 *   regex.h
 *
 *   return a pointer to a structure that represents the regular expression
 *   pattern described by the string argument;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef REGEXMAKE_SOURCE
#define REGEXMAKE_SOURCE

#include <limits.h>
#include <string.h>
#include <ctype.h>

#include "../regex/regex.h"
#include "../tools/memory.h"
#include "../chrlib/chrlib.h"

regexp *regexmake (char const *string) 

{
	char buffer [UCHAR_MAX + 1] = 
	{
		0
	};
	regexp * pattern = (regexp *) (0);
	regexp * current = (regexp *) (0);
	if (string) while (*string) 
	{
		if (pattern) 
		{
			current = current->next = NEW (regexp);
		}
		else 
		{
			current = pattern = NEW (regexp);
		}
		memset (current, 0, sizeof (regexp));
		switch (*string) 
		{
		case REGEX_C_ESC:
			if (*++string) 
			{
				current->exclude = false;
				buffer [0] = (char) (chruesc (*string));
				buffer [1] = (char) (0);
				string++;
			}
			else 
			{
				current->exclude = false;
				buffer [0] = (char) REGEX_C_ESC;
				buffer [1] = (char) (0);
			}
			break;
		case REGEX_C_SRT:
			if (*++string == REGEX_C_NOT) 
			{
				current->exclude = true;
				string++;
			}
			else 
			{
				current->exclude = false;
			}
			string = charset (string, REGEX_C_END, buffer, sizeof (buffer));
			if (*string) 
			{
				string++;
			}
			break;
		case REGEX_C_ANY:
			current->exclude = true;
			buffer [0] = (char) (0);
			buffer [1] = (char) (0);
			string++;
			break;
		default:
			current->exclude = false;
			buffer [0] = *string;
			buffer [1] = (char) (0);
			string++;
			break;
		}
		current->charset = strdup (buffer);
		switch (*string) 
		{
		case REGEX_C_KLEENE_ONCE:
			current->minimum = 0;
			current->maximum = 1;
			string++;
			break;
		case REGEX_C_KLEENE_STAR:
			current->minimum = 0;
			current->maximum = REGEX_COUNT_MAX;
			string++;
			break;
		case REGEX_C_KLEENE_PLUS:
			current->minimum = 1;
			current->maximum = REGEX_COUNT_MAX;
			string++;
			break;
		default:
			current->minimum = 1;
			current->maximum = 1;
			break;
		}
		current->next = (regexp *) (0);
	}
	return (pattern);
}


#endif

