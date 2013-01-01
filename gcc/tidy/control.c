/*====================================================================*
 *   
 *   void control (signed c, signed e);
 *
 *   tidy.h
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

#ifndef CONTROL_SOURCE
#define CONTROL_SOURCE

#include <stdio.h>

#include "../tidy/tidy.h"

signed control (signed c, signed e) 

{
	while ((c != e) && (c != EOF)) 
	{
		c = content (c);
	}
	return (c);
}


#endif

