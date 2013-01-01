/*====================================================================*
 *
 *   TREE *findnode(TREE *node, void *name, int comp (void *name, void *data));
 *
 *   tree.h
 *
 *   search a TREE structure for a named node and return the node address;
 *   return NULL if the named node does not exist.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FINDNODE_SOURCE
#define FINDNODE_SOURCE

#include "../tree/tree.h"

TREE *findnode (TREE * node, void const *name, int comp (void const *, void const *)) 

{
	if (comp != (void *) (0)) 
	{
		while (node != (TREE *) (0)) 
		{
			int order = comp (name, node->name);
			if (order < 0) 
			{
				node = node->one;
			}
			else if (order > 0) 
			{
				node = node->two;
			}
			else 
			{
				break;
			}
		}
	}
	return (node);
}


#endif

