/*====================================================================*
 *
 *   signed ctoupper (signed c);
 *
 *   chrtype.h
 *
 *   return the upper case equivalent of aaracte; only lower letters are
 *   affected; other characters are returned unmodified.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CTOUPPER_SOURCE
#define CTOUPPER_SOURCE

#include "../chrlib/chrtype.h"

signed ctoupper (signed c) 

{
	return ((c < 'a') || (c > 'z')? c: c - ('a' - 'A'));
}


#endif

