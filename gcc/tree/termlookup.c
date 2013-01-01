/*====================================================================*
 *
 *   TREE *termlookup (TREE * tree, char const *name, int comp (char const *, char const *));
 *   
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef TERMLOOKUP_SOURCE
#define TERMLOOKUP_SOURCE

#include "../tree/tree.h"

char const * termlookup (TREE * node, char const *name, int comp (char const *, char const *)) 

{
	if (comp != (void *) (0)) 
	{
		while (node != (TREE *) (0)) 
		{
			int order = comp (name, (char const *)(node->name));
			if (order < 0) 
			{
				node = node->one;
				continue;
			}
			if (order > 0) 
			{
				node = node->two;
				continue;
			}
			return ((char const *)(node->data));
		}
	}
	return (name);
}


#endif

