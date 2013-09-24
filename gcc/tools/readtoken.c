/*====================================================================*
 *
 *   int readtoken(int fd, char buffer[], size_t length);
 *
 *   fetch next token from stdin and return the token class;
 *
 *   earlier version of this function used do {...} while instead of
 *   while {...} to avoid an unecessary loop exit test; this test is
 *   now tolerated because we check for sp overrun for each damn 
 *   character; 
 *
 *   this version includes optional code that treats literal strings
 *   and c language comments as distinct tokens; the extra character
 *   variable is used to read ahead, allowing c to store the initial
 *   character value; this decision keeps the logic very general; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef READTOKEN_SOURCE
#define READTOKEN_SOURCE

#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

#include "../tools/tools.h"
#include "../tools/chars.h"

int readtoken(signed fd, char * buffer, size_t length)

{
	static int c = (char)(0);
	static int n = 0;
	if (buffer != (char *)(0))
	{
		if (n < 1)
		{
			n = read(fd, & c, 1);
		}
		if (n < 1)
		{
			* buffer = (char)(0);
			return (EOF);
		}
		else if(isblank(c))
		{
			do 
			{
				* buffer++ = (char)(c);
				n = read(fd, & c, 1);
			}
			while ((n > 0) && isblank(c) && (length-- > 1));
			* buffer = (char)(0);
			return (' ');
		}
		else if(isalpha(c))
		{
			do 
			{
				* buffer++ = (char)(c);
				n = read(fd, & c, 1);
			}
			while ((n > 0) && isalnum(c) && (length-- > 1));
			* buffer = (char)(0);
			return ('A');
		}
		else if(isdigit(c))
		{
			do 
			{
				* buffer++ = (char)(c);
				n = read(fd, & c, 1);
			}
			while ((n > 0) && isdigit(c) && (length-- > 1));
			* buffer = (char)(0);
			return ('0');
		}
		else 
		{
			buffer [0] = (char)(c);
			buffer [1] = (char)(0);
			n = read(fd, & c, 1);
			return (* buffer);
		}
	}
	return (- 1);
}

#endif



