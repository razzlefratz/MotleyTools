/*====================================================================*
 *
 *   void menudump (MENU * menu, char * string, char buffer [], size_t length);
 *   
 *   menu.h 
 *
 *   print menu on stdout in a format that can be read by menuload;
 *   buffer must accomodate the longest menu string; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MENUDUMP_SOURCE
#define MENUDUMP_SOURCE

#include <stdio.h>

#include "../menu/menu.h"

void menudump (MENU * menu, char * string, char buffer [], size_t length) 

{
	if (menu->prior) 
	{
		menudump (menu->prior, string, buffer, length);
	}
	*string = menu->ascii;
	if (menu->equal) 
	{
		menudump (menu->equal, string + 1, buffer, length);
	}
	else 
	{
		printf ("%03d ", menu->class);
		printf ("%03d ", menu->value);
		printf ("%s\n", buffer);
	}
	if (menu->after) 
	{
		menudump (menu->after, string, buffer, length);
	}
	return;
}


#endif

