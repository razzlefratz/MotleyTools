/*====================================================================*
 *
 *   void termreport(TREE *tree);
 *
 *   print an alphabetical listing of nodes by recursively searching
 *   the tree inorder;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef NAMESORT_SOURCE
#define NAMESORT_SOURCE

#include <stdio.h>

#include "../tree/tree.h"

void termreport (TREE *node, char const * format) 

{
	if (node != (TREE *) (0)) 
	{
		termreport (node->one, format);
		if ((format != (char const *)(0)) && (*format != (char)(0))) 
		{
			printf (format, (char *)(node->name), (char *)(node->data));
		}
		termreport (node->two, format);
	}
	return;
}


#endif

