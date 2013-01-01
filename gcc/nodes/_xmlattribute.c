/*====================================================================*
 *
 *   struct node const * _xmlattribute (struct node const * node);
 *
 *   nodes.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _XMLATTRIBUTE_SOURCE
#define _XMLATTRIBUTE_SOURCE

#include <stdio.h>

#include "../nodes/nodes.h"

struct node const * _xmlattribute (struct node const * node) 

{
	if (node) 
	{
		node = node->below;
	}
	while ((node) && (node->type == NODE_ATTR)) 
	{
		printf (" %s", node->text);
		_xmlvalue (node);
		node = node->after;
	}
	if (!node) 
	{
		printf ("/");
	}
	return (node);
}


#endif

