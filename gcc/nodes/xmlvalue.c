/*====================================================================*
 *
 *   struct node * xmlvalue (struct node const * node);
 *
 *   nodes.h
 *
 *   search an attribute node for the value node and return the 
 *   value node address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef XMLVALUE_SOURCE
#define XMLVALUE_SOURCE

#include <string.h>

#include "../nodes/nodes.h"

struct node const * xmlvalue (struct node const * node) 

{
	if (node) 
	{
		node = node->below;
	}
	while (node) 
	{
		if (node->type == NODE_VALU) 
		{
			return (node);
		}
		node = node->after;
	}
	return (node);
}


#endif

