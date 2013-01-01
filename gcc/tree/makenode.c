/*====================================================================*
 *
 *   TREE *makenode(void const *name, void *data);
 *
 *   tree.h
 *
 *   allocate a TREE structure and initialize it with the specified 
 *   name and data values; return the node address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MAKENODE_SOURCE
#define MAKENODE_SOURCE

#include "../tree/tree.h"
#include "../tools/memory.h"

TREE *makenode (void *name, void *data) 

{
	TREE *node = NEW (TREE);
	node->one = node->two = (TREE *)(0);
	node->name = (void *)(name);
	node->data = (void *)(data);
	return (node);
}


#endif

