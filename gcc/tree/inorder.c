/*====================================================================*
 *
 *   void sorttree(TREE *tree, void *data, void func (TREE *, void *))
 *
 *   tree.h
 *
 *   recursively visit each node of a TREE structure in in-order and
 *   perform the specified function on each node using the node data
 *   and the specified data;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef INORDER_SOURCE
#define INORDER_SOURCE

#include "tree.h"

void inorder (TREE * node, void *data, void func (TREE *, void *)) 

{
	if (node != (TREE *) (0)) 
	{
		if (func != (void *) (0)) 
		{
			inorder (node->one, data, func);
			func (node, data);
			inorder (node->two, data, func);
		}
	}
	return;
}


#endif

