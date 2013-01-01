/*====================================================================*
 *
 *   MENU * menuprefix (MENU * menu, char const * string)
 *
 *   menu.h 
 *
 *   return node only if string is a unique prefix;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MENUPREFIX_SOURCE
#define MENUPREFIX_SOURCE

#include "../menu/menu.h"

MENU * menuprefix (MENU * menu, char const * string) 

{
	while (menu && *string) 
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
		menu = menu->equal;
		string++;
	}
	while (menu) 
	{
		if (menu->prior) 
		{
			menu = (MENU *)(0);
			continue;
		}
		if (menu->after) 
		{
			menu = (MENU *)(0);
			continue;
		}
		if (menu->equal) 
		{
			menu = menu->equal;
			continue;
		}
		break;
	}
	return (menu);
}


#endif

