/*====================================================================*
 *
 *   char *chrdef(char ctable[], char const *charset);
 *
 *   chrlib.h
 *
 *   populate a character table with either the specified byte value 
 *   in charset or NUL. For example, "abc" places ASCII the code for 
 *   'a', 'b' and 'c' in those cells but "-abc" places NUL in those
 *   cells:
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CHRDEF_SOURCE
#define CHRDEF_SOURCE

#include "../regex/regex.h"
#include "../chrlib/chrlib.h"

void chrdef (char ctable [], char const *charset) 

{

#ifdef CMASSOC_SAFEMODE

	if (!charset) 
	{
		return;
	}

#endif

	if (*charset == REGEX_C_NOT) 
	{
		while (*charset) 
		{
			ctable [(unsigned) (*charset)] = (char) (0);
			charset++;
		}
	}
	else 
	{
		while (*charset) 
		{
			ctable [(unsigned) (*charset)] = *charset;
			charset++;
		}
	}
	return;
}


#endif

