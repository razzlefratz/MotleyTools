/*====================================================================*
 *
 *   int strxcmp(char const *string1, char const *string2, const unsigned char table[]);
 *
 *   strlib.h
 *
 *   compare two strings and return -1, 0 or 1 to indicate that the first
 *   string lexographically precedes, matches or follows the second using
 *   the specified collating sequence.
 *
 *   the collating sequence is table driven; the absolute character value
 *   is used to retrieve the relative character value used in comparison;
 *
 *   For example, if 'B' is to precede 'A' then fill table['B'] with some
 *   value that is less than table['A']; it's all up to you;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRXCMP_SOURCE
#define STRXCMP_SOURCE

#include "../strlib/strlib.h"

int strxcmp (register char const *string1, register char const *string2, register const unsigned char order []) 

{
	if (string1 == string2) 
	{
		return (0);
	}
	if (!string1) 
	{
		return (-1);
	}
	if (!string2) 
	{
		return (+1);
	}
	while (order [(unsigned)(*string1)] == order [(unsigned)(*string2)]) 
	{
		if (!order [(unsigned)(*string1)]) 
		{
			return (0);
		}
		string1++;
		string2++;
	}
	return (order [(unsigned)(*string1)] < order [(unsigned)(*string2)]? -1: +1);
}


#endif

