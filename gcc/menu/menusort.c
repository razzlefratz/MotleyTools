/*====================================================================*
 *
 *   void menusort (MENU * menu, char * string, char buffer [], size_t length);
 *   
 *   menu.h 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MENUSORT_SOURCE
#define MENUSORT_SOURCE

#include <stdio.h>
#include "../menu/menu.h"

void menusort (MENU * menu, char * string, char buffer [], size_t length) 

{
	if (menu->prior) 
	{
		menusort (menu->prior, string, buffer, length);
	}
	*string = menu->ascii;
	if (menu->equal) 
	{
		menusort (menu->equal, string + 1, buffer, length);
	}
	else 
	{
		printf ("%s\n", buffer);
	}
	if (menu->after) 
	{
		menusort (menu->after, string, buffer, length);
	}
	return;
}


#endif

