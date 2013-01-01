/*====================================================================*
 *
 *   struct node const * xmlelement (struct node const * node, char const * name);
 *
 *   nodes.h
 *   
 *   search a document node for a named element node and return the 
 *   element node address;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

#ifndef XMLELEMENT_SOURCE
#define XMLELEMENT_SOURCE

#include <string.h>

#include "../nodes/nodes.h"

struct node const * xmlelement (struct node const * node, char const * name) 

{
	if (node) 
	{
		node = node->below;
	}
	while (node) 
	{
		if (node->type == NODE_ELEM) 
		{
			struct node const * temp;
			if (!strcmp (node->text, name)) 
			{
				return (node);
			}
			temp = xmlelement (node, name);
			if (temp) 
			{
				return (temp);
			}
		}
		node = node->after;
	}
	return (node);
}


#endif

