/*====================================================================*
 *
 *   void xmltree (struct node const * node);
 *
 *   nodes.h
 *
 *   print node structure on stdout;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef XMLTREE_SOURCE
#define XMLTREE_SOURCE

#include <stdio.h>

#include "../nodes/nodes.h"
#include "../tools/format.h"

void xmltree (struct node const * node) 

{
	static signed level = 0;
	if (node) 
	{
		node = node->below;
	}
	while (node) 
	{

#if 0

		printf ("%04d ", node->index);
		printf ("%02d ", node->level);
		printf ("%04d ", node->count);

#endif

		printf ("%04d ", node->line);
		printf ("[%c] ", node->type);
		indent (level, "[%s]", node->text);
		level++;
		xmltree (node);
		level--;
		node = node->after;
	}
	return;
}


#endif

