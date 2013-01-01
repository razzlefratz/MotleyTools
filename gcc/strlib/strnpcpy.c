/*====================================================================*
 *
 *   char *strnpcpy(char *buffer, char const *string, size_t count)
 *
 *   strlib.h
 *
 *   copy no more than a specified number of characters from a string to
 *   a buffer; return the address of the NUL terminator;
 *
 *   this function can be implemented by the following macro ...
 *
 *   #define _strnpcpy(bp,sp,n) _strchr(_strncpy((bp),(sp),(n)),NUL)
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRNPCPY_SOURCE
#define STRNPCPY_SOURCE

#include "../strlib/strlib.h"

char *strnpcpy (register char * buffer, register char const * string, size_t count) 

{
	if (buffer) if (string) 
	{
		while ((*string) && (count-- > 0)) 
		{
			*buffer++ = *string++;
		}
		*buffer = (char)(0);;
	}
	return (buffer);
}


#endif

