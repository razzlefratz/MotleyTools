/*====================================================================*
 *   
 *   TREE * dictdefine (TREE * node, char const *name, char const *text);
 *   
 *   dict.h
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef DICTDEFINE_SOURCE
#define DICTDEFINE_SOURCE

#include <string.h>

#include "../tools/memory.h"
#include "../tree/dict.h"
#include "../tree/tree.h"
#include "../link/link.h"

TREE *dictdefine (TREE * node, char const *name, char const *text) 

{
	int order;
	if (node == (TREE *) (0)) 
	{
		node = NEW (TREE);
		node->one = node->two = (TREE *) (0);
		node->name = (void *) (strdup (name));
		node->data = (void *) (0);
	}
	order = strcmp (name, (char const *)(node->name));
	if (order < 0) 
	{
		node->one = dictdefine (node->one, name, text);
	}
	else if (order > 0) 
	{
		node->two = dictdefine (node->two, name, text);
	}
	else 
	{
		LINK *item = NEW (LINK);
		item->next = (LINK *) (node->data);
		item->name = (void *) (strdup (text));
		item->data = (void *) (0);
		node->data = (void *) (item);
	}
	return (node);
}


#endif

