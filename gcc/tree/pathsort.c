/*====================================================================*
 *
 *   pathsort.c -
 *
 *   sort pathnames using an N-Tier tree;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *%  Packaged as cmassoc-tools-1.4.2 by cmaier@cmassoc.net;
 *
 *--------------------------------------------------------------------*/

#ifndef PATHSORT_SOURCE
#define PATHSORT_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/memory.h"
#include "../tools/types.h"
#include "../tree/tree.h"

/*====================================================================*
 *
 *   TREE *catalog (TREE * node, char const *name[], int comp (char const *, char const *));
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

TREE *catalog (TREE * node, char const *name [], int comp (char const *, char const *)) 

{
	if (name == (char const **) (0)) 
	{
		return (node);
	}
	if (*name == (char *) (0)) 
	{
		return (node);
	}
	if (**name == (char) (0)) 
	{
		return (node);
	}
	if (node == (TREE *) (0)) 
	{
		node = NEW (TREE);
		node->one = node->two = node->sub = (TREE *) (0);
		node->name = (void *) (strdup (*name));
		node->data = (void *) (0);
		node->size = 0;
	}
	if (comp != (void *) (0)) 
	{
		signed order = comp (*name, node->name);
		if (order < 0) 
		{
			node->one = catalog (node->one, name, comp);
		}
		else if (order > 0) 
		{
			node->two = catalog (node->two, name, comp);
		}
		else 
		{
			node->sub = catalog (node->sub, ++name, comp);
			node->size++;
		}
	}
	return (node);
}


/*====================================================================*
 *
 *   void collate (TREE * node, char buffer[], size_t length, size_t offset, flag_t flags);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void collate (TREE * node, char buffer [], size_t length, size_t offset, flag_t flags) 

{
	if (node != (TREE *) (0)) 
	{
		size_t count = offset;
		collate (node->one, buffer, length, offset, flags);
		if (node->sub != (TREE *) (0)) 
		{
			count += snprintf (buffer + count, length - count, "%s.", (char *)(node->name));
			collate (node->sub, buffer, length - count, count, flags);
		}
		else 
		{
			count += snprintf (buffer + count, length - count, "%s\n", (char *)(node->name));
			fputs (buffer, stdout);
		}
		collate (node->two, buffer, length, offset, flags);
	}
	return;
}


/*====================================================================*
 *    
 *--------------------------------------------------------------------*/

#endif

