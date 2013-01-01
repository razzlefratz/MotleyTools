/*====================================================================*
 *
 *   signed ctoascii(signed c);
 *
 *   chrtype.h
 *
 *   return the 7 bit ASCII value of the integer argument;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CTOASCII_SOURCE
#define CTOASCII_SOURCE

#include "../chrlib/chrtype.h"

signed ctoascii (signed c) 

{
	return ((unsigned)(c)&(0x007F));
}


#endif

