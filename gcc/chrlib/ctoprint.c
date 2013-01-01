/*====================================================================*
 *
 *   signed ctoprint (signed c);
 *
 *   chrtype.h
 *
 *   return the ANSI control code for an ASCII control character; .
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CTOPRINT_SOURCE
#define CTOPRINT_SOURCE

#include "../chrlib/chrtype.h"

signed ctoprint (signed c) 

{
	return ((unsigned)(c)|(0x0040));
}


#endif

