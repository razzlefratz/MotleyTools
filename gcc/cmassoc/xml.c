/*====================================================================*
 *
 *   xml.c - xml file enumeration;
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../nodes/nodes.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#include "../tools/emalloc.c"
#include "../tools/indent.c"
#endif

#ifndef MAKEFILE
#include "../nodes/_xmlattribute.c"
#include "../nodes/_xmlvalue.c"
#include "../nodes/xmlread.c"
#include "../nodes/xmltree.c"
#include "../nodes/xmlstream.c"
#include "../nodes/xmlindent.c"
#include "../nodes/xmlnode.c"
#include "../nodes/xmlscan.c"
#include "../nodes/xmlfree.c"
#include "../nodes/reorder.c"
#endif

/*====================================================================*
 *
 *   void csstree (struct node const * node);
 *
 *   search node for "style" attributes and print a template css 
 *   statement for each; use the form "element.class { }" so that
 *   properties can be added as needed;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void csstree (struct node const * node)

{
	if (node)
	{
		node = node->below;
	}
	while ((node) && (node->type == NODE_ATTR))
	{
		if (! strcmp (node->text, "class"))
		{
			printf ("%s.%s { }\n", node->above->text, node->below->text);
		}
		csstree (node);
		node = node->after;
	}
	return;
}

/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
 *   
 *   
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv [])

{
	static char const * optv [] = 
	{
		"cdst",
		PUTOPTV_S_FUNNEL,
		"enumerate html/xhtml/xml document fragments",
		"c\tprint CSS stylesheet on stdout",
		"d\tprint document as text",
		"s\tprint document as stream",
		"t\tprint document as tree",
		(char const *) (0)
	};
	struct node node;
	void (* xmldump) (struct node const *) = xmlindent;
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'c':
			xmldump = csstree;
			break;
		case 'd':
			xmldump = xmlindent;
			break;
		case 's':
			xmldump = xmlstream;
			break;
		case 't':
			xmldump = xmltree;
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		error (1, ENOTSUP, "No filenames given!");
	}
	while ((argc) && (* argv))
	{
		xmlread (& node, * argv);
		xmlscan (& node);
		reorder (& node);
		xmldump (& node);
		xmlfree (& node);
		argc--;
		argv++;
	}
	return (0);
}

