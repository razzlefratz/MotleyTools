/*====================================================================*
 *
 *   struct node const * xmlcontent (struct node const * node);
 *
 *   nodes.h
 *   
 *   search an element node for the next data node and return the
 *   data node address;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

#ifndef XMLDATA_SOURCE
#define XMLDATA_SOURCE

#include <string.h>

#include "../nodes/nodes.h"

struct node const * xmlcontent (struct node const * node) 

{
	if (node) 
	{
		node = node->below;
	}
	while (node) 
	{
		if (node->type == NODE_DATA) 
		{
			return (node);
		}
		node=node->after;
	}
	return (node);
}


#endif

