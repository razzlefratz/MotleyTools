/*====================================================================*
 *
 *   chroct.c - convert character to octal string;
 *
 *   chrlib.h
 *
 *   character to character code conversions are messy to code inline
 *   and generally do not justify the overhead of loops and counters; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CHROCT_SOURCE
#define CHROCT_SOURCE

#include "../chrlib/chrlib.h"
#include "../tools/number.h"

char *chrtooctal (char *string, unsigned c) 

{

#ifdef CMASSOC_SAFEMODE

	if (string == (char *) (0)) 
	{
		return (string);
	}

#endif

	*string++ = DIGITS_OCT [(c >> 6) & (unsigned) (3)];
	*string++ = DIGITS_OCT [(c >> 3) & (unsigned) (7)];
	*string++ = DIGITS_OCT [(c >> 0) & (unsigned) (7)];
	*string = (char) (0);
	return (string);
}

char *chrtounix (char *string, unsigned c) 

{

#ifdef CMASSOC_SAFEMODE

	if (string == (char *) (0)) 
	{
		return (string);
	}

#endif

	*string++ = '\\';
	string = chrtooctal (string, c);
	return (string);
}


#endif

