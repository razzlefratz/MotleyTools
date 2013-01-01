/*====================================================================*
 *
 *   static size_t splitpath (size_t level, size_t limit, char *stack[], char pathname[]);
 *
 *   files.h
 *
 *   split pathname into filename components and push them on the
 *   filename stack; if pathname starts with slash then clear the 
 *   stack before starting; if the pathname is void or empty then
 *   return without action; 
 *
 *   the stack is cummulative; absolute paths reset the stack and
 *   relative paths extend it;
 *
 *   ths stack is implemented as a NULL terminated string vector;
 *   the pathname buffer must remain intact until the application
 *   discards the stack;                               
 *
 *   the stack should be big enough for all pathnames; otherwise
 *   the last stack item will contain multiple path components;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SPLITPATH_SOURCE
#define SPLITPATH_SOURCE

#include "../files/files.h"

size_t splitpath (size_t level, size_t limit, char const *stack [], char pathname []) 

{
	if (pathname == (char *) (0)) 
	{
		return (level);
	}
	if (*pathname == (char) (0)) 
	{
		return (level);
	}
	if (*pathname == PATH_C_EXTENDER) 
	{
		level = 0;
	}
	for (stack [level++] = pathname; *pathname != (char) (0); pathname++) 
	{
		if (*pathname == PATH_C_EXTENDER) 
		{
			if (level < limit) 
			{
				stack [level++] = pathname + 1;
				*pathname = (char) (0);
			}
		}
	}
	stack [level] = (char *)(0);
	return (level);
}


#endif

