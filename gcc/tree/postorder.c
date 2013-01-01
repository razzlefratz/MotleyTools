/*====================================================================*
 *
 *   void postorder (TREE * node, void *data, void func (TREE *, void *));
 *
 *   tree.h
 *
 *   recursively visit each node of a TREE structure in post-order and
 *   perform the specified function on each node using the node data
 *   and the specified data;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef POSTORDER_SOURCE
#define POSTORDER_SOURCE

#include "../tree/tree.h"

void postorder (TREE * node, void *data, void func (TREE *, void *)) 

{
	if (node != (TREE *) (0)) 
	{
		if (func != (void *) (0)) 
		{
			postorder (node->one, data, func);
			postorder (node->two, data, func);
			func (node, data);
		}
	}
	return;
}


#endif

