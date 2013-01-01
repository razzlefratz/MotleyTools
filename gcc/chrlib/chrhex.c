/*====================================================================*
 *
 *   chrhex.c - convert character to octal string;
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

#ifndef CHRHEX_SOURCE
#define CHRHEX_SOURCE

#include "../chrlib/chrlib.h"
#include "../tools/number.h"

char *chrtohex (char *string, unsigned c) 

{

#ifdef CMASSOC_SAFEMODE

	if (string == (char *) (0)) 
	{
		return (string);
	}

#endif

	*string++ = DIGITS_HEX [(c >> 4) & 0x0F];
	*string++ = DIGITS_HEX [(c >> 0) & 0x0F];
	*string = (char)(0);
	return (string);
}

char *chrtoietf (char *string, unsigned c) 

{

#ifdef CMASSOC_SAFEMODE

	if (string == (char *) (0)) 
	{
		return (string);
	}

#endif

	*string++ = '%';
	string = chrtohex (string, c);
	return (string);
}

char *chrtoiso (char *string, unsigned c) 

{

#ifdef CMASSOC_SAFEMODE

	if (string == (char *) (0)) 
	{
		return (string);
	}

#endif

	*string++ = '#';
	*string++ = 'x';
	string = chrtohex (string, c);
	return (string);
}

char *chrtohtml (char *string, unsigned c) 

{

#ifdef CMASSOC_SAFEMODE

	if (string == (char *) (0)) 
	{
		return (string);
	}

#endif

	*string++ = '&';
	string = chrtoiso (string, c);
	*string++ = ';';
	*string = (char)(0);
	return (string);
}

char *chrtoconst (char *string, unsigned c) 

{

#ifdef CMASSOC_SAFEMODE

	if (string == (char *) (0)) 
	{
		return (string);
	}

#endif

	*string++ = '0';
	*string++ = 'x';
	string = chrtohex (string, c);
	return (string);
}


#endif

