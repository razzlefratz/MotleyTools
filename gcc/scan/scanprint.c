/*====================================================================*
 *
 *   void scanprint (SCAN * content, signed fd);
 *
 *   scan.h
 * 
 *   write the current token to the device associated with a file
 *   descriptor; this function is identical to writetoken but adds
 *   a newline character after each write;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SCANPRINT_SOURCE
#define SCANPRINT_SOURCE

#include <unistd.h>

#include "../scan/scan.h"

void scanprint (SCAN * content, signed fd) 

{
	write (fd, content->first, content->final - content->first);
	write (fd, "\n", 1);
	return;
}


#endif

