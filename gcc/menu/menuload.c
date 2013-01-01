/*====================================================================*
 *
 *   MENU * menuload (MENU * menu, char buffer[], size_t length)
 *   
 *   menu.h 
 *
 *   fill a menu structure with symbols from stdin; input consists of
 *   one or more lines containing an integer class, integer value and 
 *   string; for example:
 *
 *      0 0 symbol
 *      0 1 symbol
 *      1 1 symbol
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MENULOAD_SOURCE
#define MENULOAD_SOURCE

#include <stdio.h>
#include <ctype.h>

#include "../menu/menu.h"
#include "../tools/chars.h"

MENU * menuload (MENU * menu, char buffer [], size_t length) 

{
	char *sp = buffer;
	signed c = getc (stdin);;
	signed group = 0;
	signed value = 0;
	while (c != EOF) 
	{
		while (isblank (c)) 
		{
			c = getc (stdin);
		}
		if (!isspace (c)) 
		{
			for (group = 0; isdigit (c); c = getc (stdin)) 
			{
				group *= 10;
				group += c - '0';
			}
			while (isblank (c)) 
			{
				c = getc (stdin);
			}
			for (value = 0; isdigit (c); c = getc (stdin)) 
			{
				value *= 10;
				value += c - '0';
			}
			while (isblank (c)) 
			{
				c = getc (stdin);
			}
			for (sp = buffer; isalnum (c); c = getc (stdin)) 
			{
				if ((size_t)(sp - buffer) < length) 
				{
					*sp++ = (char)(c);
				}
			}
			*sp = (char)(0);
			menu = menudefine (menu, buffer, group, value);
		}
		while (isspace (c)) 
		{
			c = getc (stdin);
		}
	}
	return (menu);
}


#endif

