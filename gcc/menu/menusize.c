/*====================================================================*
 *
 *   void menusize (MENU * menu);
 *   
 *   menu.h 
 *
 *   return the number of nodes in a menu;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MENUSIZE_SOURCE
#define MENUSIZE_SOURCE

#include <stdio.h>
#include "../menu/menu.h"

unsigned menusize (MENU * menu) 

{
	unsigned size = 0;
	if (menu->prior) 
	{
		size += menusize (menu->prior);
	}
	if (menu->equal) 
	{
		size += menusize (menu->equal);
	}
	else 
	{
		size++;
	}
	if (menu->after) 
	{
		size += menusize (menu->after);
	}
	return (size);
}


#endif

