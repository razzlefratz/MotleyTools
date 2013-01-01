/*====================================================================*
 *
 *   signed ctocntrl(signed c);
 *
 *   chrtype.h
 *
 *   return the ASCII control character that corresponds to a printable
 *   character; for example:
 *
 *      <bel> = _ctocntrl('G')
 *      <ht>  = _ctocntrl('I');
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CTOCNTRL_SOURCE
#define CTOCNTRL_SOURCE

#include "../chrlib/chrtype.h"

signed ctocntrl (signed c) 

{
	return (((c <= 0x0040) || (c >= 0x0060))? (c): (c)&(0x001F));
}


#endif

