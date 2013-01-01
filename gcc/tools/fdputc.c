/*====================================================================*
 *
 *   signed fdputc (signed fd, char c);
 *
 *   memory.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FDPUTC_SOURCE
#define FDPUTC_SOURCE

#include <stdio.h>
#include <unistd.h>

signed fdputc (signed fd, char c) 

{
	return (write (fd, &c, sizeof (c)) == sizeof (c)? c: EOF);
}


#endif

