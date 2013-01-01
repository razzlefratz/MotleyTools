/*====================================================================*
 *
 *   void preorder(TREE *node, void * data, void func (TREE *, void *));
 *
 *   tree.h
 *
 *   visit each node of a TREE structure in pre-order and perform the
 *   specified function using the node data and the specified data;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef PREORDER_SOURCE
#define PREORDER_SOURCE

#include "../tree/tree.h"

void preorder (TREE * node, void *data, void func (TREE *, void *)) 

{
	if (node != (TREE *) (0)) 
	{
		if (func != (void *) (0)) 
		{
			func (node, data);
			preorder (node->one, data, func);
			preorder (node->two, data, func);
		}
	}
	return;
}


#endif

