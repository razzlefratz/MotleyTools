/*====================================================================*
 *
 *   void menuvolume (MENU * menu);
 *   
 *   menu.h 
 *
 *   return the number of non-NUL characters in the menu tree; this
 *   number should be less than the characters comprising all words
 *   in the tree; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MENUVOLUME_SOURCE
#define MENUVOLUME_SOURCE

#include <stdio.h>
#include "../menu/menu.h"

unsigned menuvolume (MENU * menu) 

{
	signed volume = 0;
	if (menu->prior) 
	{
		volume += menuvolume (menu->prior);
	}
	if (menu->equal) 
	{
		volume += menuvolume (menu->equal) + 1;
	}
	if (menu->after) 
	{
		volume += menuvolume (menu->after);
	}
	return (volume);
}


#endif

