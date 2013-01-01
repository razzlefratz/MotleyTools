/*====================================================================*
 *
 *   signed ctolower (signed c);
 *
 *   chrtype.h
 *
 *   return the lower case equivalent of a character;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CTOLOWER_SOURCE
#define CTOLOWER_SOURCE

#include "../chrlib/chrtype.h"

signed ctolower (signed c) 

{
	return ((c < 'A') || (c > 'Z')? (c): (c)+('a'-'A'));
}


#endif

