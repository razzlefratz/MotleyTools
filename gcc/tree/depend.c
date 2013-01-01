/*====================================================================*
 *
 *   depend.c - dependency orderng functions;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef DEPEND_SOURCE
#define DEPEND_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include <string.h>
#include <memory.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/memory.h"
#include "../link/link.h"
#include "../tree/tree.h"
#include "../tree/depend.h"

/*====================================================================*
 *   extern variables
 *--------------------------------------------------------------------*/

TREE *nodetree = (TREE *) (0);
LINK *nodelist = (LINK *) (0);

/*====================================================================*
 *
 *   TREE * storenode (TREE * tree, TREE * node, char const * name, void * data, int (* comp) (char const *, char const *));
 *
 *   create the named node and attach data to it; return the node
 *   address; 
 *
 *   this function creates the master list of node names and data 
 *   for network and dependency analysis; 
 *
 *   the list is maintained as binary tree where each node.has a name
 *   and a data pointer; name pointers refer to strings; data pointers 
 *   can refer to anything, such as a data structure or linked list
 *   or binary tree or whatever; the algorithm is standardi stuff;
 *
 *   as new nodes are added to the tree, this function also adds 
 *   them to a circular linked list for traversal purposes; this
 *   step was inserted here for efficiency and can be removed; the
 *   the tree and the list interact in the following way:
 *
 *   we add nodes to the tree; new nodes are appended to the list;
 *   old nodes are ignored; an external program starts searching
 *   nodes in the list for neighbor nodes and adds them to the tree;
 *   
 *   new and old nodes are quickly distiguished by the tree search; 
 *   new nodes go into the tree and onto the list pending a visit 
 *   by the search program; this ensures that nodes are not 
 *   revisited; the list can be discarded or saved;
 *    
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

TREE * storenode (TREE * node, TREE * edge, char const * name, void * data, int (* comp) (char const *, char const *)) 

{
	if (!node) 
	{
		LINK *nodeitem = NEW (LINK);
		nodeitem->name = strdup (name);
		if (nodelist) 
		{
			nodeitem->next = nodelist->next;
			nodelist->next = nodeitem;
		}
		else 
		{
			nodeitem->next = nodeitem;
		}
		nodelist = nodeitem;
		node = NEW (TREE);
		memset (node, 0, sizeof (TREE));
		node->name = nodeitem->name;
	}
	if (comp) 
	{
		signed order = comp (name, node->name);
		if (order < 0) 
		{
			node->one = storenode (node->one, edge, name, data, comp);
		}
		else if (order > 0) 
		{
			node->two = storenode (node->two, edge, name, data, comp);
		}
		else if (edge) 
		{
			edge->name = node->name;
			node->data = data;
		}
		else 
		{
			node->data = data;
		}
	}
	return (node);
}


/*====================================================================*
 *
 *   TREE * fetchnode (TREE * tree, char const *name, int (* comp) (char const *, char const *));
 *
 *   find the named node and return the node address, if present; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

TREE * fetchnode (TREE * tree, char const * name, int (* comp) (char const *, char const *)) 

{
	if (comp) while (tree) 
	{
		int order = comp (name, tree->name);
		if (order < 0) 
		{
			tree = tree->one;
		}
		else if (order > 0) 
		{
			tree = tree->two;
		}
		else 
		{
			break;
		}
	}
	return (tree);
}


/*====================================================================*
 *
 *   TREE * ordernode (TREE * tree, char const * source, char const * target, int (* comp) (char const *, char const *))
 *
 *   define the relationship between name and data if not already defined;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

TREE * ordernode (TREE * edge, char const * source, char const * target, int (* comp) (char const *, char const *)) 

{
	extern TREE *nodetree;
	if (!edge) 
	{
		edge = NEW (TREE);
		memset (edge, 0, sizeof (TREE));
		nodetree = storenode (nodetree, edge, source, (void *)(0), comp);
	}
	if (comp) 
	{
		signed order = (comp) (source, edge->name);
		if (order < 0) 
		{
			edge->one = ordernode (edge->one, source, target, comp);
		}
		else if (order > 0) 
		{
			edge->two = ordernode (edge->two, source, target, comp);
		}
		else if (target) 
		{
			edge->sub = ordernode (edge->sub, target, (char const *)(0), comp);
		}
	}
	return (edge);
}


/*====================================================================*
 *
 *   void enumerate (TREE *tree);
 *
 *   print an alphabetical listing of network nodes by recursively 
 *   searching the tree inorder;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void enumerate (TREE * tree) 

{
	if (tree) 
	{
		enumerate (tree->one);
		printf ("%s\n", (char *)(tree->name));
		enumerate (tree->two);
	}
	return;
}


/*====================================================================*
 *
 *   void structure (TREE * tree);
 *
 *   print an alpabetical and indented list of sources and targets;
 *   the significance of source or target is application dependent; 
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void structure (TREE * tree) 

{
	if (tree) 
	{
		structure (tree->one);
		printf ("%s\n", (char *)(tree->name));
		component (tree->sub);
		printf ("\n");
		structure (tree->two);
	}
	return;
}


/*====================================================================*
 *
 *   void component (TREE * tree);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void component (TREE * tree) 

{
	if (tree) 
	{
		component (tree->one);
		printf ("\t%s\n", (char *)(tree->name));
		component (tree->two);
	}
	return;
}


#endif

