/*====================================================================*
 *
 *   signed ctodigit (unsigned c);
 *
 *   chrtype.h
 *   
 *   return the `signed integer equivalent of an ASCII digit or the
 *   value CHAR_MAX on error;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CTODIGIT_SOURCE
#define CTODIGIT_SOURCE

#include <limits.h>

#include "../chrlib/chrtype.h"

signed ctodigit (signed c) 

{
	if ((c >= '0') && (c <= '9')) 
	{
		return (c - '0');
	}
	if ((c >= 'A') && (c <= 'Z')) 
	{
		return (c - 'A' + 10);
	}
	if ((c >= 'a') && (c <= 'z')) 
	{
		return (c - 'a' + 10);
	}
	return (CHAR_MAX);
}


#endif

