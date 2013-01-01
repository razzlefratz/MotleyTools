/*====================================================================*
 *
 *   NODE * xmlnode (NODE * root);
 *
 *   nodes.h
 *   
 *   create an empty node and attach it as the last child below the
 *   root node;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef XMLNODE_SOURCE
#define XMLNODE_SOURCE

#include <memory.h>

#include "../nodes/nodes.h"
#include "../tools/memory.h"

NODE * xmlnode (NODE * root) 

{
	NODE * node = NEW (NODE);
	memset (node, 0, sizeof (NODE));
	if (!root) 
	{
		return (node);
	}
	if (root->below) 
	{
		NODE * temp = root->below;
		while (temp->after) 
		{
			temp = temp->after;
		}
		node->above = root;
		temp->after = node;
		node->prior = temp;
		return (node);
	}
	root->below = node;
	node->above = root;
	return (node);
}


#endif

