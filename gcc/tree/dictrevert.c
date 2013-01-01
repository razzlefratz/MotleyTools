/*====================================================================*
 *   
 *   void dictrevert (TREE * node, char const *name);
 *   
 *   dict.h
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef DICTREVERT_SOURCE
#define DICTREVERT_SOURCE

#include <string.h>
#include <stdlib.h>

#include "dict.h"
#include "../tree/tree.h"
#include "../link/link.h"

void dictrevert (TREE * node, char const *name) 

{
	while (node != (TREE *) (0)) 
	{
		int order = strcmp (name, node->name);
		if (order < 0) 
		{
			node = node->one;
		}
		else if (order > 0) 
		{
			node = node->two;
		}
		else if (node->data) 
		{
			LINK *item = (LINK *) (node->data);
			node->data = (LINK *) (item->next);
			free (item->name);
			free (item);
			break;
		}
		else 
		{
			break;
		}
	}
	return;
}


#endif

