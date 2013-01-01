/*====================================================================*
 *   
 *   void dictreport (TREE * node);
 *   
 *   dict.h
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef DICTREPORT_SOURCE
#define DICTREPORT_SOURCE

#include <stdio.h>

#include "../tree/tree.h"
#include "dict.h"
#include "../link/link.h"

void dictreport (TREE * node) 

{
	if (node != (TREE *) (0)) 
	{
		LINK *item;
		printf ("%s\n", (char const *)(node->name));
		for (item = (LINK *)(node->data); item != (LINK *) (0); item = item->next) 
		{
			printf ("\t[%s]\n", (char const *)(item->name));
		}
		dictreport (node->one);
		dictreport (node->two);
	}
	return;
}


#endif

