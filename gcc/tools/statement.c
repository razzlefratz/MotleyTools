/*====================================================================*
 *
 *   size_t statement (int fd, char buffer[], size_t length, size_t *lineno);
 *
 *   tools.h
 *
 *   return a complete statement for a configuration file; exclude
 *   comment lines and empty lines; condense strings of spaces and 
 *   tabs to one space; concatenate continuation lines to form one
 *   line;
 *
 *   if the next character is space or tab then replace it with a
 *   space, unless it is the first buffer character, then advance
 *   the buffer position and read characters into it until a non-
 *   blank, non-tab character is read; 
 *
 *   if the next character is hash then read characters into that
 *   position until newline is read, then read the next character 
 *   into that position and increment the line counter;
 *
 *   if the next character is backslash then read the next into 
 *   that position; if it is newline then read the next into that
 *   position and increment the line counter; otherwise, proceed
 *   without incrementing the counter; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STATEMENT_SOURCE
#define STATEMENT_SOURCE

#include <unistd.h>
#include <ctype.h>

#include "../tools/tools.h"
#include "../tools/chars.h"

size_t statement (int fd, char buffer [], size_t length, size_t * lineno) 

{
	char *string = buffer;
	int count = read (fd, string, 1);
	length--;
	while (count > 0) 
	{
		if (*string == '#') 
		{
			do 
			{
				count = read (fd, string, 1);
			}
			while ((count > 0) && (*string != '\n'));
			continue;
		}
		if (isblank (*string)) 
		{
			if (string == buffer) 
			{
				count = read (fd, string, 1);
				break;
			}
			if (string < (buffer + length)) 
			{
				*string++ = ' ';
			}
			do 
			{
				count = read (fd, string, 1);
			}
			while ((count > 0) && isblank (*string));
			continue;
		}
		if (*string == '\\') 
		{
			count = read (fd, string, 1);
			if (*string == '\n') 
			{
				count = read (fd, string, 1);
				if (lineno != (size_t *) (0)) 
				{
					(*lineno)++;
				}
			}
			continue;
		}
		if (*string == '\n') 
		{
			if (lineno) 
			{
				(*lineno)++;
			}
			if (string == buffer) 
			{
				count = read (fd, string, 1);
				break;
			}
			count = 0;
			continue;
		}
		if (string < (buffer + length)) 
		{
			string++;
		}
		count = read (fd, string, 1);
	}
	length++;
	if (string < (buffer + length)) 
	{
		*string = (char) (0);
	}
	return (string - buffer);
}


/*====================================================================*
 *   test program;
 *--------------------------------------------------------------------*/

#if 0
#include <unistd.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>

int main (int argc, char const *argv []) 

{
	char buffer [100];
	size_t lineno = 0;
	file_t fd;
	if ((fd = open (*++argv, O_RDONLY)) == -1) 
	{
		error (1, errno, "can't open %s", *argv);
	}
	while (statement (fd, buffer, sizeof (buffer), &lineno)) 
	{
		printf ("%d [%s]\n", lineno, buffer);
	}
	close (fd);
	return;
}


#endif

#endif

