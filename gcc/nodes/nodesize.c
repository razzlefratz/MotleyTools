/*====================================================================*
 *
 *   unsigned nodesize(NODE *node);
 *
 *   nodes.h
 *
 *   return the number of nodes in a structure.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef NODESIZE_SOURCE
#define NODESIZE_SOURCE

#include "../nodes/nodes.h"

unsigned nodesize (NODE * node) 

{
	unsigned size = 0;
	if (node) 
	{
		size += nodesize (node->below);
		size += nodesize (node->after);
		size += 1;
	}
	return (size);
}


#endif

