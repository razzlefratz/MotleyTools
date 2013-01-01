/*====================================================================*
 *
 *   void chrescmap (const unsigned char table [], char escape);    
 *
 *   chrlib.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CHRESCMAP_SOURCE
#define CHRESCMAP_SOURCE

#include <stdio.h>
#include <limits.h>

#include "../chrlib/chrlib.h"

void chrescmap (const unsigned char table [], char escape) 

{
	extern char const * sv_ascii [UCHAR_MAX + 1];
	unsigned c;
	for (c = 0; c < (UCHAR_MAX + 1); c++) 
	{
		if (c != table [c]) 
		{
			printf (" %03d %s \"%c%c\"\n", c, sv_ascii [table [c]], escape, table [c]);
		}
	}
	return;
}


#endif

