/*====================================================================*
 *
 *   signed fdgetc (signed fd);
 *
 *   memory.h
 *
 *   a file descripter version of getc();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FDGETC_SOURCE
#define FDGETC_SOURCE

#include <stdio.h>
#include <unistd.h>

signed fdgetc (signed fd) 

{
	char c;
	return (read (fd, &c, sizeof (c)) == sizeof (c)? c: EOF);
}


#endif

