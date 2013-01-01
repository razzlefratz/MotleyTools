/*====================================================================*
 *
 *   char *strmin(char string[], char const *punct, char const *space, char const *trash)
 *
 *   strlib.h
 *
 *   Remove redundant white space and trash from a buffer. Remove spaces
 *   around punctuation. Preserve one space between adjacent punctuation
 *   and all spaces between other text. Remove trash found anywhere.
 *
 *   Characters that constitute punctuation, space and trash are defined
 *   using three strings. By convention, characters found in any of them
 *   are replaced with the first character in the string (except trash).
 *
 *   For example, if the punctuation string were ",;:" then the occurance
 *   of any of these characters will be replaced by ',' where appropriate
 *   and surrounding spaces will be removed.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRMIN_SOURCE
#define STRMIN_SOURCE

#include <string.h>
#include "../strlib/strlib.h"

char *strmin (char string [], char const *punct, char const *space, char const *trash) 

{
	register char *sp,
	*cp;
	int npunct = 0;
	int nspace = 0;
	int ntrash = 0;
	for (sp = cp = string; *cp; cp++) 
	{
		if (strchr (punct, *cp)) 
		{
			npunct++;
		}
		else if (strchr (space, *cp)) 
		{
			nspace = 1;
		}
		else if (strchr (trash, *cp)) 
		{
			ntrash = 0;
		}
		else 
		{
			if (sp > string) 
			{
				if (npunct > 0) 
				{
					while (npunct-- > 0) 
					{
						*sp++ = *punct;
					}
				}
				else if (nspace > 0) 
				{
					while (nspace-- > 0) 
					{
						*sp++ = *space;
					}
				}
				else if (ntrash > 0) 
				{
				}
			}
			npunct = nspace = ntrash = 0;
			*sp++ = *cp;
		}
	}
	*sp = *cp;
	return (string);
}


#endif

