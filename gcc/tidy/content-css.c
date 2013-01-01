/*====================================================================*
 *   
 *   void content (int c, char const *string);
 *   
 *   read stdin and write stdout; copy characters up to the next
 *   occurance of any delimiter in string; replace strings of white
 *   space with one space; ignore characters inside literals, groups
 *   and C style comments; 
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

#ifndef CONTENT_CSS_SOURCE
#define CONTENT_CSS_SOURCE

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "../tidy/tidy.h"
#define TIDY_CSS2
#include "../tidy/content.c"

#endif

