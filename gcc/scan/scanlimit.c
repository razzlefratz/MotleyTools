/*====================================================================*
 *
 *   void scanlimit (SCAN * content);
 *
 *   scan.h
 * 
 *   expand the token to include the balance of the input buffer 
 *   by setting the charcter pointer to the limit pointer;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SCANLIMIT_SOURCE
#define SCANLIMIT_SOURCE

#include "../scan/scan.h"

void scanlimit (SCAN * content) 

{
	content->final = content->limit;
	return;
}


#endif

