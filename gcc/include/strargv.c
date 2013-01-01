/*====================================================================*
 *
 *   size_t strargv (size_t argc, char const *argv[], char buffer[], unsigned c);
 *
 *   update string vector argv[] with arguments parsed from buffer;
 *   return the actual argument count as the function value; integer
 *   argc is the size of argv[]; character c, if present, terminates
 *   parsing; parsing always terminates on NUL, anyway;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRARGV_SOURCE
#define STRARGV_SOURCE

#include <ctype.h>

#include "../strlib/strlib.h"
#include "../chrlib/chrlib.h"

size_t strargv (size_t argc, char const *argv [], char buffer [], unsigned c) 

{
	char const **argp = argv;
	char *string = buffer;

#ifdef STRLIB_SAFEMODE

	if (argv == (char const **) (0)) 
	{
		return ((size_t)(0));
	}
	if (buffer == (char *) (0)) 
	{
		return ((size_t)(0));
	}

#endif

	if (argc-- > 1) 
	{
		while (isspace (*buffer)) 
		{
			buffer++;
		}
		if ((*buffer != (char) (0)) && (*buffer != (char) (c))) 
		{
			*argv++ = string;
		}
		while (((argv - argp) < argc) && (*buffer != (char) (0)) && (*buffer != (char) (c))) 
		{
			if (isquote (*buffer)) 
			{
				char quote = *buffer++;
				while ((*buffer != (char) (0)) && (*buffer != quote) && (*buffer != (char) (c))) 
				{
					if (*buffer == '\\') 
					{
						*string++ = *buffer++;
					}
					if (*buffer != (char) (0)) 
					{
						*string++ = *buffer++;
					}
				}
				if (*buffer == quote) 
				{
					buffer++;
				}
			}
			else if (*buffer == '\\') 
			{
				*string++ = *buffer++;
				if (*buffer != (char) (0)) 
				{
					*string++ = *buffer++;
				}
			}
			else 
			{
				*string++ = *buffer++;
			}
			if (isspace (*buffer)) 
			{
				while (isspace (*buffer)) 
				{
					buffer++;
				}
				*string++ = (char) (0);
				if ((*buffer != (char) (0)) && (*buffer != (char) (c))) 
				{
					*argv++ = string;
				}
			}
		}
		*string = (char) (0);
		*argv = (char *) (0);
	}
	return (argv - argp);
}


#endif

