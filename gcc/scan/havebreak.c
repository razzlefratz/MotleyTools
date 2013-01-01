/*====================================================================*
 *
 *   bool havebreak(SCAN * content, char const *charset);
 *
 *   scan.h
 *
 *   advance to the next input buffer character only if the current
 *   current input buffer character is in charset; this function is
 *   useful for detecting optional delimiters;
 *
 *   For example:
 *
 *   scanalpha (&content);
 *   if (havebreak (&content, "="))
 *   {
 *      scandigit (&content);
 *   }
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef HAVEBREAK_SOURCE
#define HAVEBREAK_SOURCE

#include "../scan/scan.h"

bool havebreak (SCAN * content, char const *charset) 

{
	if (isbreak (content, charset)) 
	{
		nextbreak (content);
		return (true);
	}
	return (false);
}


#endif

