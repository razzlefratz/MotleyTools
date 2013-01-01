/*====================================================================*
 *
 *   bool ischarset(char const *string, char const *charset);
 *
 *   strlib.h
 *
 *   return true if all characters in the first string are members of
 *   the second; return false if any characters are not memebers;
 *
 *   for example, if ischarset(string, "0123456789") == true then string
 *   contains only digits and nothing else.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <string.h>
#include "../strlib/strlib.h"

bool ischarset (register char const *string, register char const *charset) 

{
	if (string != (char *)(0)) 
	{
		while ((*string != (char)(0)) && (strchr (charset, *string) != (char *)(0))) 
		{
			string++;
		}
	}
	return (string != (char *)(0)? (*string != (char)(0)? false: true): false);
}

