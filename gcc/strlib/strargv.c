/*====================================================================*
 *
 *   size_t strargv (size_t argc, char const * argv [], char * string, signed c);
 *
 *   strlib.h
 *
 *   parse a string for command line arguments and return them in
 *   an argument vector; return the actual argument count; 
 *
 *   argc is the vector size; c is a non-null termination character;
 *   no globbing or escape character replacement is done; 
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

size_t strargv (size_t argc, char const * argv [], register char * string, register signed c) 

{
	char const **argp = argv;

#ifdef CMASSOC_SAFEMODE

	if (!argv) 
	{
		return ((size_t)(0));
	}
	if (!buffer) 
	{
		return ((size_t)(0));
	}

#endif

	while (argc-- > 0) 
	{
		while ((*string == ' ') || (*string == '\t')) 
		{
			*string++ = (char)(0);
		}
		if ((*string == c) || (*string == (char)(0))) 
		{
			break;
		}
		*argv++ = string;
		if ((*string == '\"') || (*string == '\'')) 
		{
			char quote = *string++;
			while ((*string != quote) && (*string != (char) (0))) 
			{
				if (*string == '\\') 
				{
					string++;
				}
				if (*string != (char) (0)) 
				{
					string++;
				}
			}
			if (*string == quote) 
			{
				string++;
			}
			continue;
		}
		if (*string == '\\') 
		{
			string++;
			if (*string) 
			{
				string++;
			}
			continue;
		}
		while ((*string) && (*string != ' ') && (*string != '\t') && (*string != c)) 
		{
			string++;
		}
	}
	*string = (char) (0);
	*argv = (char *) (0);
	return (argv - argp);
}


#endif

