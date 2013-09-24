/*====================================================================*
 *
 *   void more (unsigned int line, unsigned int page, FILE * fp);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MORE_SOURCE
#define MORE_SOURCE

#include <stdio.h>
#include <unistd.h>

void more(unsigned int line, unsigned int page, FILE * fp)

{
	if (fp == (FILE *) (0))
	{
		return;
	}
	if (isatty(fileno(fp)) == 0)
	{
		return;
	}
	if ((line > 0) && (page > 0) && (line % page == 0))
	{
		signed c;
		write (STDOUT_FILENO, " -more- ", 8);
		read (STDOUT_FILENO, & c, 1);
		write (STDOUT_FILENO, "\r", 1);
	}
	return;
}

#endif



