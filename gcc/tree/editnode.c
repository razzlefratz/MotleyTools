/*====================================================================*
 *
 *   TREE *editnode(TREE * node, void const *name, void *data, void *edit (void *, void *));
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

#ifndef EDITNODE_SOURCE
#define EDITNODE_SOURCE

#include <string.h>

#include "../tree/tree.h"

TREE *editnode (TREE * node, void const *name, void *data, void *edit (void *, void *)) 

{
	while (node != (TREE *) (0)) 
	{
		int order = strcmp (name, node->name);
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
		if (edit) 
		{
			node->data = edit (node->data, data);
			continue;
		}
		if (data) 
		{
			node->data = data;
			continue;
		}
		break;
	}
	return (node);
}


#endif

