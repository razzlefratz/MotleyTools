/*====================================================================*
 *
 *   TREE *termdefine (TREE *tree, char const *name, void const *data, int comp (char const *, char const *));
 *   
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef TERMDEFINE_SOURCE
#define TERMDEFINE_SOURCE

#include "../tools/memory.h"
#include "../tree/tree.h"

TREE * termdefine (TREE *node, char const *name, char const * text, int comp (char const *, char const *)) 

{
	if (node == (TREE *) (0)) 
	{
		node = NEW (TREE);
		node->one = node->two = (TREE *) (0);
		node->name = (void *)(name);
		node->data = (void *)(0);
	}
	if (comp != (void *) (0)) 
	{
		signed order = comp (name, (char const *)(node->name));
		if (order < 0) 
		{
			node->one = termdefine (node->one, name, text, comp);
		}
		else if (order > 0) 
		{
			node->two = termdefine (node->two, name, text, comp);
		}
		else 
		{
			node->data = (void *)(text);
		}
	}
	return (node);
}


#endif

