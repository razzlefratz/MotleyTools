/*====================================================================*
 *
 *   void chrtbl (const unsigned char table [], FILE *fp);    
 *
 *   chrlib.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CHRTBL_SOURCE
#define CHRTBL_SOURCE

#include <stdio.h>
#include <limits.h>

#include "../chrlib/chrlib.h"

void chrtbl (const unsigned char table [], FILE *fp) 

{
	extern char const * sv_ascii [UCHAR_MAX + 1];
	unsigned c;
	for (c = 0; c < sizeof (* sv_ascii); c++) 
	{
		if (c != table [c]) 
		{
			fprintf (fp, " [%03d]:[%s]=[%03d]:[%s]\n", c, sv_ascii [c], table [c], sv_ascii [table [c]]);
		}
	}
	return;
}


#endif

