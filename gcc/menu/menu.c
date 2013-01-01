/*====================================================================*
 *
 *   menu.c - 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *%  Packaged as cmassoc-tools-1.3.11 by cmaier@cmassoc.net;
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../menu/menu.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/emalloc.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../menu/menudefine.c"
#include "../menu/menulookup.c"
#include "../menu/menuprefix.c"
#include "../menu/menuload.c"
#include "../menu/menudump.c"
#include "../menu/menushow.c"
#include "../menu/menusize.c"
#include "../menu/menulist.c"
#endif

/*====================================================================*
 *   program constants;  
 *--------------------------------------------------------------------*/

#define MENU_DUMP (1 << 0)
#define MENU_SHOW (1 << 1)

/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const *argv []) 

{
	static char const *optv [] = 
	{
		"dm",
		"",
		"menu demo/test program",
		"d\tdump menu table",
		"m\tshow menu table",
		(char const *) (0)
	};
	MENU * menu = (MENU *)(0);
	char buffer [80];
	flag_t flags = (flag_t) (0);
	signed c;
	optind = 1;
	opterr = 1;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'm':
			_setbits (flags, MENU_SHOW);
			break;
		case 'd':
			_setbits (flags, MENU_DUMP);
			break;
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	menu = menuload (menu, buffer, sizeof (buffer));
	if (_anyset (flags, MENU_DUMP)) 
	{
		menudump (menu, buffer, buffer, sizeof (buffer));
	}
	if (_anyset (flags, MENU_SHOW)) 
	{
		menushow (menu, buffer, sizeof (buffer));
	}
	while ((argc) && (*argv)) 
	{
		MENU * item = menuprefix (menu, *argv);
		if (item) 
		{
			printf ("+ %s %d %d\n", *argv, item->class, item->value);
		}
		else 
		{
			printf ("- %s\n", *argv);
		}
		argc--;
		argv++;
	}
	return (0);
}

