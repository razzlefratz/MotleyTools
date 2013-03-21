/*====================================================================*
 *   
 *   void endline (signed space);
 *   
 *   tidy.h
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

#ifndef ENDLINE_SOURCE
#define ENDLINE_SOURCE

#include <stdio.h>

#include "../tidy/tidy.h"

char const * finish = TIDY_S_FINISH;
char const * record = TIDY_S_RECORD;

void endline (signed space) 

{
	extern char const *finish;
	extern char const *record;
	for (fputs (finish, stdout); space-- > 0; fputs (record, stdout));
	return;
}


#endif

