/*====================================================================*
 *
 *   NODE * xmlfree (NODE * node);
 *
 *   nodes.h
 *
 *   recursively free child nodes; minimize recursion by following  
 *   node->after at each level; 
 *
 *   the caller must free the root node; this allows that the root
 *   to be statically declared, if desired;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef XMLFREE_SOURCE
#define XMLFREE_SOURCE

#include <stdlib.h>
#include <memory.h>

#include "../nodes/nodes.h"

void xmlfree (NODE * node) 

{
	if (node) 
	{
		node = node->below;
	}
	while (node) 
	{
		NODE * temp = node;
		if (node->above) 
		{
			node->above->below = (NODE *)(0);
		}
		if (node->prior) 
		{
			node->prior->after = (NODE *)(0);
		}
		xmlfree (node);
		node = node->after;
		free (temp);
	}
	return;
}


#endif

