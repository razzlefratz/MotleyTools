/*====================================================================*
 *
 *   bool haveclass(SCAN * content, char const *charset);
 *
 *   scan.h 
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef HAVECLASS_SOURCE
#define HAVECLASS_SOURCE

#include "../scan/scan.h"

bool haveclass (SCAN * content, char const *charset) 

{
	if (isclass (content, charset)) 
	{
		nexttoken (content);
		return (true);
	}
	return (false);
}


#endif

