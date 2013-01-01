/*====================================================================*
 *
 *   size_t mergepath (size_t count, size_t limit, char const *stack[]);
 *
 *   scan string vector stack[] containing pathname elements; remove
 *   unecessary components like "", "." and ".." ;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MERGEPATH_SOURCE
#define MERGEPATH_SOURCE

#include "../files/files.h"

size_t mergepath (size_t count, size_t limit, char const *stack []) 

{
	size_t index;
	size_t start;
	for (index = start = limit = 1; index < count; index++) 
	{
		size_t dots;
		for (dots = 0; stack [index][dots] == FILE_C_EXTENDER; dots++);
		if (stack [index][dots] != (char) (0)) 
		{
			stack [limit++] = stack [index];
			continue;
		}
		if (dots > 2) 
		{
			stack [limit++] = stack [index];
			continue;
		}
		if (dots > 1) 
		{
			if (limit == start) 
			{
				stack [limit++] = stack [index];
				start++;
			}
			else 
			{
				limit--;
			}
			continue;
		}
	}
	stack [limit] = (char *)(0);
	return (limit);
}


#endif

