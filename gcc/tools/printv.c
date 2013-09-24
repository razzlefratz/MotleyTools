/*====================================================================*
 *
 *   void printv(char const *vector[], size_t count);
 *
 *   print a string vector to the specified output stream;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>

#include "../tools/tools.h"

signed printv(char const * vector[], size_t count)

{
	size_t index;
	signed nchar;
	for (index = nchar = 0; (index < count) && (vector[index] != (char *) (0)); index++)
	{
		nchar += printf("%03zd %s\n", index, vector[index]);
	}
	nchar += printf("\n");
	return (nchar);
}

