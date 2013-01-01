/*====================================================================*
 *
 *   void scanwrite (SCAN * content, signed fd);
 *
 *   scan.h
 * 
 *   write the current token to the device associated with a file
 *   descriptor;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SCANWRITE_SOURCE
#define SCANWRITE_SOURCE

#include <unistd.h>

#include "../scan/scan.h"

void scanwrite (SCAN * content, signed fd) 

{
	write (fd, content->first, content->final - content->first);
	return;
}


#endif

