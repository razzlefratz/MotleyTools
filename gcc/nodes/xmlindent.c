/*====================================================================*
 *
 *   void xmlindent (struct node const * node);
 *
 *   nodes.h
 *
 *   print node structure on stdout in XML format with indenting;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef XMLINDENT_SOURCE
#define XMLINDENT_SOURCE

#include <stdio.h>
#include <errno.h>

#include "../nodes/nodes.h"
#include "../tools/error.h"

void xmlindent (struct node const * node) 

{
	static unsigned level = 0;
	while (node) 
	{
		unsigned count = level;
		if (!node->type) 
		{
			xmlindent (node->below);
		}
		else if (node->type == NODE_SGML) 
		{
			while (count--) 
			{
				putc ('\t', stdout);
			}
			printf ("<!%s", node->text);
			_xmlattribute (node);
			printf (">\n");
		}
		else if (node->type == NODE_ELEM) 
		{
			struct node const * temp;
			while (count--) 
			{
				putc ('\t', stdout);
			}
			printf ("<%s", node->text);
			temp = _xmlattribute (node);
			printf (">\n");
			level++;
			xmlindent (temp);
			level--;
		}
		else if (node->type == NODE_ETAG) 
		{
			while (count--) 
			{
				putc ('\t', stdout);
			}
			printf ("</%s>\n", node->text);
		}
		else if (node->type == NODE_PROC) 
		{
			printf ("<%s>\n", node->text);
		}
		else if (node->type == NODE_CODE) 
		{
			printf ("<%s>\n", node->text);
		}
		else if (node->type == NODE_DATA) 
		{
			while (count--) 
			{
				putc ('\t', stdout);
			}
			printf ("%s\n", node->text);
		}
		else 
		{
			error (0, ENOTSUP, "Unclassified node: [%c] '%s'", node->type, node->text);
		}
		node = node->after;
	}
	return;
}


#endif

