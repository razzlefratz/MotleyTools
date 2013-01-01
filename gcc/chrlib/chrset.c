/*====================================================================*
 *
 *   void chrset (char ctable []);
 *
 *   chrlib.h
 *
 *   fill every element of a character table with its own index if 
 *   mode is true or with NUL if mode is false;
 *
 *   use chrdef() or chrsub() to modify selected table elements;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CHRSET_SOURCE
#define CHRSET_SOURCE

#include <limits.h>

#include "../chrlib/chrlib.h"

void chrset (char ctable []) 

{
	unsigned c;
	for (c = 0; c < (UCHAR_MAX + 1); c++) 
	{
		ctable [c] = c;
	}
	return;
}


#endif

