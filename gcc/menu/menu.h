/*====================================================================*
 *
 *   menu.h -
 *
 *.  Motley Tools by Charles Maier
 *:  Published 2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MENU_HEADER
#define MENU_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <unistd.h>
#include <stdint.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/types.h"

/*====================================================================*
 *   variables;
 *--------------------------------------------------------------------*/

typedef struct menu 

{
	struct menu * prior;
	struct menu * equal;
	struct menu * after;
	signed class;
	signed value;
	signed ascii;
}

MENU;

/*====================================================================*
 *   functions;
 *--------------------------------------------------------------------*/

void menusort (MENU * menu, char * string, char buffer [], size_t length);
void menudump (MENU * menu, char * string, char buffer [], size_t length);
MENU * menuload (MENU * menu, char buffer [], size_t length);
void menushow (MENU * menu, char buffer [], signed length);
unsigned menusize (MENU * menu);
unsigned menulength (MENU * menu, signed length);
unsigned menuvolume (MENU * menu);
char ** menulist (MENU * menu, char * string, char buffer [], size_t length, char * vector [], size_t size);
MENU * menudefine (MENU * menu, char const * string, signed class, signed value);
MENU * menuitem (char const * string, signed class, signed value);
MENU * menulookup (MENU * menu, char const * string);
MENU * menuprefix (MENU * menu, char const * string);
MENU * menuassume (MENU * menu, char const * string);

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

