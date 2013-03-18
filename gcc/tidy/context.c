/*====================================================================*
 *   
 *   signed context (signed c, signed e);
 *
 *   tidy.h
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

#ifndef CONTEXT_SOURCE
#define CONTEXT_SOURCE

#include "../tidy/tidy.h"

signed context (signed c, signed e) 

{
	c = keep (c);
	c = control (c, e);
	c = keep (e);
	return (c);
}


#endif

