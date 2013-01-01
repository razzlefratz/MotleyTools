/*====================================================================*
 *
 *   void menulength (MENU * menu);
 *   
 *   menu.h 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MENULENGTH_SOURCE
#define MENULENGTH_SOURCE

#include <stdio.h>

#include "../menu/menu.h"

unsigned menulength (MENU * menu, signed length) 

{
	signed count = 0;
	if (menu->prior) 
	{
		count = menulength (menu->prior, length);
	}
	if (menu->equal) 
	{
		count = menulength (menu->equal, length++);
	}
	if (menu->after) 
	{
		count = menulength (menu->after, length);
	}
	return (length);
}


#endif

