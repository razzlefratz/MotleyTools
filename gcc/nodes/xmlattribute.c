/*====================================================================*
 *
 *   struct node const * xmlattribute (struct node const * node, char const * name);
 *
 *   nodes.h
 *   
 *   search an element node for the named attribute node and return
 *   that node address;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

#ifndef XMLATTRIBUTE_SOURCE
#define XMLATTRIBUTE_SOURCE

#include <string.h>

#include "../nodes/nodes.h"

struct node const * xmlattribute (struct node const * node, char const * name) 

{
	if (node) 
	{
		node = node->below;
	}
	while ((node) && (node->type == NODE_ATTR) && strcmp (node->text, name)) 
	{
		node = node->after;
	}
	return (node);
}


#endif

