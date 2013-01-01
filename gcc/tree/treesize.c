/*====================================================================*
 *
 *   unsigned treesize(TREE *node);
 *
 *   tree.h
 *
 *   count the number of nodes in a tree structure.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef TREESIZE_SOURCE
#define TREESIZE_SOURCE

#include "../tree/tree.h"

unsigned treesize (TREE * node) 

{
	unsigned size = 0;
	if (node) 
	{
		size += treesize (node->one);
		size += treesize (node->two);
		size += 1;
	}
	return (size);
}


#endif

