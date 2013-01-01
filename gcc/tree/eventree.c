/*====================================================================*
 *
 *   TREE *eventree(TREE *node);
 *
 *   tree.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "tree.h"

TREE *eventree (TREE *node) 

{
	TREE *root;
	TREE *temp;
	if (node) 
	{
		root = node;
		if (node->one == (TREE *)(0)) 
		{
			if (node->two != (TREE *)(0)) 
			{
				temp = node = node->two;
				while (temp->one != (TREE *)(0)) temp = temp->one;
				temp->one = root;
				root->two = (TREE *)(0);
			}
		}
		else if (node->two == (TREE *)(0)) 
		{
			if (node->one != (TREE *)(0)) 
			{
				temp = node = node->one;
				while (temp->two != (TREE *)(0)) temp = temp->two;
				temp->two = root;
				root->one = (TREE *)(0);
			}
		}
		node->one = eventree (node->one);
		node->two = eventree (node->two);
	}
	return (node);
}

