/*====================================================================*
 *
 *   char ** menulist (MENU * menu, char * string, char buffer [], size_t length, char * list [], size_t size);
 *
 *   menu.h 
 *
 *   return a string vector containing an ordered list of menu items;    
 *   buffer must be long enough to hold the longest menu string; menu
 *   is searched recusively; no sorting is needed; all vector strings
 *   must be freed after use; call menusize() to determine the number 
 *   of menu items;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MENULIST_SOURCE
#define MENULIST_SOURCE

#include <unistd.h>
#include <string.h>

#include "../menu/menu.h"

char ** menulist (MENU * menu, char * string, char buffer [], size_t length, char * list [], size_t items) 

{
	if (menu) 
	{
		list = menulist (menu->prior, string, buffer, length, list, items);
		*string = menu->ascii;
		if (menu->equal) 
		{
			list = menulist (menu->equal, string + 1, buffer, length, list, items);
		}
		else if (items) 
		{
			*list++ = strdup (buffer);
			items--;
		}
		list = menulist (menu->after, string, buffer, length, list, items);
	}
	return (list);
}


#endif

