/*====================================================================*
 *
 *   char *strsub (char const *string, char const *old, char const *new, size_t count);
 *
 *   strlib.h
 *
 *   search a string for one vector and replace it with another; perform
 *   only the specified number of replacements if the vector occurs more
 *   than once;
 *
 *   a new string is always returned leaving the original intact; NULL may
 *   be returned if memory cannot be allocated or string pointers are void.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRSUB_SOURCE
#define STRSUB_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../strlib/strlib.h"

char *strsub (char const *string, char const *remove, char const *insert, size_t count) 

{
	struct _sub_ 
	{
		char const *string;
		size_t length;
	}
	*vector;
	if (string == (char *)(0));
	else if (remove == (char *)(0));
	else if (insert == (char *)(0));
	else if ((vector = malloc ((count + 1) * sizeof (struct _sub_))) != (void *)(0)) 
	{
		size_t index = 0;
		size_t stringlength = strlen (string);
		size_t removelength = strlen (remove);

/* compute here once */

		size_t insertlength = strlen (insert);

/* compute here once */

		char *result;
		vector [index].string = string;
		vector [index].length = stringlength;
		while ((index < count) && (string = strstr (string, remove))) 
		{
			vector [index].length = (size_t)(string - vector [index].string);
			index++;
			vector [index].string = string += removelength;
			vector [index].length = strlen (string);
			stringlength -= removelength;
			stringlength += insertlength;
		}
		if ((result = malloc ((stringlength + 1) * sizeof (char))) != (void *)(0)) 
		{
			result = strncat (result, vector [0].string, vector [0].length);
			for (count = 1; count <= index; count++) 
			{
				result = strncat (result, insert, insertlength);
				result = strncat (result, vector [count].string, vector [count].length);
			}
		}
		free (vector);
		return (result);
	}
	return ((char *)(0));
}


#endif

