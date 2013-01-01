/*====================================================================*
 *
 *   bool isclass (SCAN * content, char const *charset);
 *
 *   scan.h
 *
 *   return true if the current class character is a member of the given
 *   character set; comparison is case sensitive;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ISCLASS_SOURCE
#define ISCLASS_SOURCE

#include <string.h>

#include "../scan/scan.h"

bool isclass (SCAN * content, char const *charset) 

{
	if (content->class) 
	{
		return ((bool) (strchr (charset, content->class)));
	}
	return (false);
}


#endif

