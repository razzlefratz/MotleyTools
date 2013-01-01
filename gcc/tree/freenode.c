/*====================================================================*
 *
 *   TREE *freenode(TREE *node, void *data)
 *
 *   tree.h
 *
 *   Delete a TREE node after deleting attached data.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FREENODE_SOURCE
#define FREENODE_SOURCE

#include <stdlib.h>

#include "../tree/tree.h"

TREE *freenode (TREE * node, void *data, void *func (void *, void *)) 

{
	if (node) 
	{
		if (func) 
		{
			node->data = func (node->data, data);
		}
		free (node->name);
		free (node);
	}
	return ((TREE *) (0));
}


#endif

