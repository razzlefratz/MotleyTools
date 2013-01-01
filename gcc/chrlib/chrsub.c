/*====================================================================*
 *
 *   void chrsub(char ctable[], char const *charset, char const *replace)
 *
 *   chrlib.h
 *
 *   fill each element of a character table corresponding to characters
 *   in the first string with the corresponding character in the second 
 *   string, if one exists; otherwise, file the element with NUL;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CHRSUB_SOURCE
#define CHRSUB_SOURCE

#include "../chrlib/chrlib.h"

void chrsub (char ctable [], char const *charset, char const *replace) 

{

#ifdef CMASSOC_SAFEMODE

	if (!ctable) 
	{
		return;
	}
	if (!charset) 
	{
		return;
	}
	if (!replace) 
	{
		return;
	}

#endif

	while (*charset) 
	{
		ctable [(unsigned)(*charset++)] = (*replace)? (*replace++):(*replace);
	}
	return;
}


#endif

