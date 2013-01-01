/*====================================================================*
 *
 *   int cgetc (int fd);
 *
 *   return next character from stdin, normally the console; print a
 *   prompt when stdin is a tty device;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CGETC_SOURCE
#define CGETC_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int cgetc (int fd) 

{
	extern char const * program_name;
	static char c = '\n';
	if (isatty (fd) && (c == '\n')) 
	{
		write (fd, program_name, strlen (program_name));
		write (fd, ": ", 2);
	}
	if (read (fd, &c, sizeof (c)) == sizeof (c)) 
	{
		return (c);
	}
	if (isatty (fd)) 
	{
		write (fd, &c, sizeof (c));
	}
	return (EOF);
}


#endif

