/*====================================================================*
 *
 *   size_t mergepath (size_t count, size_t limit, char const *stack[]);
 * 
 *   files.h
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
	size_t index = 0;
	for (index = limit = 1; index < count; index++) 
	{
		int dots;
		for (dots = 0; stack [index][dots] == FILE_C_EXTENDER; dots++);
		if (stack [index][dots] != (char) (0)) 
		{
			stack [limit++] = stack [index];
		}
		else if (dots > 2) 
		{
			stack [limit++] = stack [index];
		}
		else if (dots > 1) 
		{
			if (limit > 1) 
			{
				limit--;
			}
		}
		else if ((index == 1) || (index == count - 1)) 
		{
			stack [limit++] = stack [index];
		}
	}
	return (limit);
}


#endif

