/*====================================================================*
 *   
 *   void newline (signed align);
 *   
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

#ifndef NEWLINE_SOURCE
#define NEWLINE_SOURCE

#include <stdio.h>

#include "../tidy/tidy.h"

char const *margin = TIDY_S_MARGIN;
char const *offset = TIDY_S_OFFSET;
void newline (signed align) 

{
	extern char const *margin;
	extern char const *offset;
	for (fputs (margin, stdout); align-- > 0; fputs (offset, stdout));
	return;
}


#endif

