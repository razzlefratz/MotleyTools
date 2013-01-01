/*====================================================================*
 *
 *   struct node const * _xmlvalue (struct node const * node);
 *
 *   nodes.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _XMLVALUE_SOURCE
#define _XMLVALUE_SOURCE

#include <stdio.h>

#include "../nodes/nodes.h"

struct node const * _xmlvalue (struct node const * node) 

{
	if (node) 
	{
		node = node->below;
	}
	if ((node) && (node->type == NODE_VALU)) 
	{
		printf ("=\"%s\"", node->text);
	}
	return (node);
}


#endif

