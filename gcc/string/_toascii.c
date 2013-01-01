/*====================================================================*
 *
 *   int _toascii(int c);
 *
 *   _ctype.h
 *
 *   return the 7 bit ASCII value of the integer argument;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../string/_ctype.h"

int _toascii (int c) 

{
	return ((unsigned)(c)&(0x007F));
}

