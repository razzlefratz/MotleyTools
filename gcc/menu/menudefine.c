/*====================================================================*
 *
 *   MENU * menudefine(MENU * menu, char const * string, signed class, signed value)
 *
 *   menu.h 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MENUDEFINE_SOURCE
#define MENUDEFINE_SOURCE

#include "../tools/tools.h"
#include "../tools/memory.h"
#include "../menu/menu.h"

MENU * menudefine (MENU * menu, char const * string, signed class, signed value) 

{
	if (!menu) 
	{
		menu = NEW (MENU);
		menu->prior = (MENU *)(0);
		menu->equal = (MENU *)(0);
		menu->after = (MENU *)(0);
		menu->ascii = *string;
		menu->class = class;
		menu->value = value;
	}
	if (*string < menu->ascii) 
	{
		menu->prior = menudefine (menu->prior, string, class, value);
	}
	else if (*string > menu->ascii) 
	{
		menu->after = menudefine (menu->after, string, class, value);
	}
	else if (*string) 
	{
		menu->equal = menudefine (menu->equal, string + 1, class, value);
	}
	else 
	{
		menu->class = class;
		menu->value = value;
	}
	return (menu);
}


#endif

