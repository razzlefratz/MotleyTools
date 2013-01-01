/*====================================================================*
 *
 *   TREE *savenode(TREE *node, void *name, int comp(void *name, void *data),
 *                  void *init, void *make (void *init, void *data),
 *                  void *data, void *func (void *link, void *data));
 *
 *   tree.h
 *
 *   search a TREE structure for the named node and call the specified
 *   function on that node; create a node if less does not exist; return
 *   the root node address;
 *
 *   savenode() is similar to findnode() but it returns the address of 
 *   the root node instead of the matching node address, and it can 
 *   create new nodes.
 *
 *   Behaviour is controlled in three parts, each consisting of a pointer
 *   to some data and a pointer to a function that can operate on that data.
 *
 *   The comparison function pointer, comp(), is used to search the tree
 *   for a named node. strcmp() or any equivalent function may be used to
 *   determine the search order. Notice that node names do not have to be
 *   character strings. If comp() is NULL then nothing happens.
 *
 *   The node allocation function pointer, make(), creates a new node and
 *   initializes it with some data; if this function is NULL then no node
 *   is created and the function returns NULL; this can be used to ensure
 *   that existing node are modified but new nodes are not created;
 *
 *   The node operation function pointer, func(), is used to attach data
 *   to a node or modify data that is already attached.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SAVENODE_SOURCE
#define SAVENODE_SOURCE

#include "../tree/tree.h"

TREE *savenode (TREE * node, void *name, int comp (void const *, void const *), void *init, void *make (void *, void *), void *data, void *edit (void *, void *)) 

{
	if (!node) 
	{
		if (make) 
		{
			node = (TREE *) (make (name, init));
		}
		else 
		{
			return (node);
		}
	}
	if (comp) 
	{
		int order = comp (name, node->name);
		if (order < 0) 
		{
			node->one = savenode (node->one, name, comp, init, make, data, edit);
		}
		else if (order > 0) 
		{
			node->two = savenode (node->two, name, comp, init, make, data, edit);
		}
		else if (edit) 
		{
			node->data = edit (node->data, data);
		}
		else if (data) 
		{
			node->data = data;
		}
		else 
		{
			return (node);
		}
	}
	return (node);
}


#endif

