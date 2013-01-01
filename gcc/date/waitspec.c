/*====================================================================*
 *
 *   time_t waitspec (char const *string);
 *
 *   tools.h
 *
 *   convert a numeric string to a positive integer timer; return
 *   the default timer if the string is void or the timer exceeds
 *   the specified range;
 *
 *   unlike atoi(), string must contain at least one decimal digit
 *   and then only decimal digits and an allowed suffix; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef WAITSPEC_SOURCE
#define WAITSPEC_SOURCE

#include <ctype.h>
#include <errno.h>

#include "../tools/tools.h"
#include "../tools/error.h"

unsigned waitspec (char const *string) 

{
	unsigned seconds = 0;
	if ((string) && (*string)) 
	{
		char const *sp;
		for (sp = string; isdigit (*sp); sp++) 
		{
			seconds *= 10;
			seconds += *sp - '0';
		}
		switch (*sp) 
		{
		case 'd':
		case 'D':
			seconds *= 24;
		case 'h':
		case 'H':
			seconds *= 60;
		case 'm':
		case 'M':
			seconds *= 60;
		case 's':
		case 'S':
			sp++;
		case '\0':
			break;
		default:
			error (1, EINVAL, "Have %s but expected 's'|'S'|'m'|'M'|'h'|'H'|'d'|'D'", string);
			break;
		}
	}
	return (seconds);
}


#endif

