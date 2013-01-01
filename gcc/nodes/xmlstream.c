/*====================================================================*
 *
 *   void xmlstream (struct node const * node);
 *
 *   nodes.h
 *
 *   print node structure on stdout in XML format without indenting;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef XMLSTREAM_SOURCE
#define XMLSTREAM_SOURCE

#include <stdio.h>
#include <errno.h>

#include "../nodes/nodes.h"
#include "../tools/error.h"

void xmlstream (struct node const * node) 

{
	while (node) 
	{
		if (!node->type) 
		{
			xmlstream (node->below);
		}
		else if (node->type == NODE_SGML) 
		{
			printf ("<!%s", node->text);
			_xmlattribute (node);
			printf (">");
		}
		else if (node->type == NODE_ELEM) 
		{
			struct node const * temp;
			printf ("<%s", node->text);
			temp = _xmlattribute (node);
			if (!temp) 
			{
				printf ("/");
			}
			printf (">");
			xmlstream (temp);
		}
		else if (node->type == NODE_ETAG) 
		{
			printf ("</%s>", node->text);
		}
		else if (node->type == NODE_PROC) 
		{
			printf ("<%s>", node->text);
		}
		else if (node->type == NODE_CODE) 
		{
			printf ("<%s>", node->text);
		}
		else if (node->type == NODE_DATA) 
		{
			printf ("%s", node->text);
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

