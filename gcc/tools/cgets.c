/*====================================================================*
 *
 *   size_t cgets (char buffer [], size_t length);
 *
 *   return console input after removing backspaces and blanking out
 *   other control characters;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CGETS_SOURCE
#define CGETS_SOURCE

#include <stdio.h>

#include "../tools/tools.h"

size_t cgets(char buffer[], size_t length)

{
	char * string = buffer;
	char * column = buffer;
	if (fgets(buffer, length, stdin))
	{
		while (length)
		{
			if (column > string)
			{
				* string = * column;
				* column = 0x00;
			}
			if (* string == 0x00)
			{
				break;
			}
			if (* string == 0x08)
			{
				if (string > buffer)
				{
					* string-- = 0x00;
				}
			}
			else if(* string < 0x20)
			{
				* string++ = 0x20;
			}
			else if(* string > 0x7E)
			{
				* string++ = 0x20;
			}
			else 
			{
				string++;
			}
			column++;
			length--;
		}
	}
	return (string - buffer);
}

#endif



