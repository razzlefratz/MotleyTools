/*====================================================================*
 *
 *   bool ismatch(SCAN * content);
 *
 *   return true if the input token character matches the first; this
 *   can be used to detect character pairs, strings of like characters
 *   or the end of quoted strings;
 *
 *--------------------------------------------------------------------*/

#ifndef ISMATCH_SOURCE
#define ISMATCH_SOURCE

#include "../scan/scan.h"

bool ismatch (SCAN * content) 

{
	return (*content->final == *content->first);
}


#endif

