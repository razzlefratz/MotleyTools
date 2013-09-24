/*====================================================================*
 *
 *   signed todigit (unsigned c);
 *
 *   number.h
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef TODIGIT_SOURCE
#define TODIGIT_SOURCE

#include <limits.h>

#include "../tools/number.h"

signed todigit(unsigned c)

{
	if ((c >= '0') && (c <= '9'))
	{
		return (c - '0');
	}
	if ((c >= 'A') && (c <= 'Z'))
	{
		return (c - 'A' +  10);
	}
	if ((c >= 'a') && (c <= 'z'))
	{
		return (c - 'a' +  10);
	}
	return (- 1);
}

#endif



