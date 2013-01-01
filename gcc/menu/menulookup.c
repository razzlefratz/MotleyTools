/*====================================================================*
 *
 *   MENU * menulookup (MENU * menu, char const * string)
 *
 *   menu.h 
 *
 *   return menu node only when string is an exact match;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MENULOOKUP_SOURCE
#define MENULOOKUP_SOURCE

#include "../menu/menu.h"

MENU * menulookup (MENU * menu, char const * string) 

{
	while (menu) 
	{
		if (*string < menu->ascii) 
		{
			menu = menu->prior;
			continue;
		}
		if (*string > menu->ascii) 
		{
			menu = menu->after;
			continue;
		}
		if (*string) 
		{
			menu = menu->equal;
			string++;
			continue;
		}
		break;
	}
	return (menu);
}


#endif

