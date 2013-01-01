/*====================================================================*
 *   
 *   void reorder (NODE * node);
 * 
 *   nodes.h
 *
 *   traverse node in preorder; update members index, level and count
 *   so that the tree can be used to represent an array or an outline;   
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef REORDER_SOURCE
#define REORDER_SOURCE

#include "../nodes/nodes.h"

void reorder (NODE * node) 

{
	static unsigned index = 0;
	static unsigned level = 0;
	while (node) 
	{
		node->index = index++;
		node->level = level;
		node->count = index;
		level++;
		reorder (node->below);
		level--;
		node->count = index - node->count;
		node = node->after;
	}
	return;
}


#endif

