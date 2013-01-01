/*====================================================================*
 *
 *   int _tocntrl(int c);
 *
 *   _ctype.h
 *
 *   return the ASCII control character that corresponds to a printable
 *   character; for example:
 *
 *      <bel> = _tocntrl('G')
 *      <ht>  = _tocntrl('I');
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../string/_ctype.h"

int _tocntrl (int c) 

{
	return ((c <= 0x0040) || (c >= 0x0060)? (c): (c)&0x001F);
}

