/*====================================================================*
 *
 *   signed cread(signed fd);
 *
 *   tools.h 
 *
 *   read a character from the file, fifo or pipe assigned to the
 *   file descriptor argument; return the character value on success 
 *   or EOF on failure;
 *
 *   this is the textbook Kernigan and Ritchie implementation for
 *   putchar with a file descriptor argument;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CREAD_SOURCE
#define CREAD_SOURCE

#include <unistd.h>

#include "tools.h"

signed cread (signed fd) 

{
	char c;
	return ((read (fd, &c, 1) > 0)? (signed) (c): EOF);
}


#endif

