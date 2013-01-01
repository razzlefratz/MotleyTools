/*====================================================================*
 *
 *   NODE * nodes (NODE * node, unsigned index);
 *
 *   nodes.h
 *
 *   treat a tree like an array; return the numbered element from the
 *   tree; use function reorder () to arrange nodes in numerical order
 *   before calling this function;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef NODES_SOURCE
#define NODES_SOURCE

#include "../nodes/nodes.h"

NODE * nodes (NODE * node, unsigned index) 

{
	while (node) 
	{
		if (node->index == index) 
		{
			break;
		}
		if (node->after) 
		{
			if (node->after->index > index) 
			{
				node = node->below;
			}
		}
		node = node->after;
	}
	return (node);
}


#endif

