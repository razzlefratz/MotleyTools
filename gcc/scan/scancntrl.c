/*====================================================================*
 *
 *   void scancntrl (SCAN * content);
 *
 *   scan.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SCANCNTRL_SOURCE
#define SCANCNTRL_SOURCE

#include <ctype.h>

#include "../scan/scan.h"

void scancntrl (SCAN * content) 

{
	while ((content->final < content->limit) && iscntrl (*content->final)) 
	{
		content->final++;
	}
	return;
}


#endif

