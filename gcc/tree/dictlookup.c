/*====================================================================*
 *   
 *   char * dictlookup (TREE * node, char const *name);
 *   
 *   dict.h
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef DICTLOOKUP_SOURCE
#define DICTLOOKUP_SOURCE

#include <string.h>

#include "dict.h"
#include "../tree/tree.h"
#include "../link/link.h"

char *dictlookup (TREE * node, char const *name) 

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
			return (((LINK *) (node->data))->name);
		}
		else 
		{
			break;
		}
	}
	return ((char *) (0));
}


#endif

