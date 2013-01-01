/*====================================================================*
 *
 *   signed cwrite (signed fd, signed c);
 *
 *   symbol.h 
 *
 *   write one character to the file descriptor argument and return  
 *   the character value on success or EOF on failure;
 *
 *   this is the textbook Kernighan and Ritchie implementation for
 *   getchar using a file descriptor argument; 
 * 
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CWRITE_SOURCE
#define CWRITE_SOURCE

#include <unistd.h>

#include "../tools/symbol.h"

signed cwrite (signed fd, signed c) 

{
	return ((write (fd, &c, 1))? (signed) (c): EOF);
}


#endif

