/*====================================================================*
 *
 *   size_t tokensize (SCAN * content);
 *
 *   scan.h
 *
 *   return the length of the current token substring; the length is
 *   computed by subtracting the start character address from
 *   the break character address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef TOKENSIZE_SOURCE
#define TOKENSIZE_SOURCE

#include "../scan/scan.h"

size_t tokensize (SCAN * content) 

{
	return (content->final - content->first);
}


#endif

