/*====================================================================*
 *
 *   void showtoken (SCAN * content);
 *
 *
 *--------------------------------------------------------------------*/

#ifndef SHOWTOKEN_SOURCE
#define SHOWTOKEN_SOURCE

#include <stdio.h>

#include "../scan/scan.h"

void showtoken (SCAN * content) 

{
	printf ("token[%c][%s]<br/>\n", content->class, tokentext (content));
	return;
}


#endif

