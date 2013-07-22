/*====================================================================*
 *
 *   order.c - topological sort program;
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

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <errno.h>
#include <ctype.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../tree/edge.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
# include "../tools/getoptv.c"
# include "../tools/putoptv.c"
# include "../tools/version.c"
# include "../tools/efreopen.c"
# include "../tools/erealloc.c"
# include "../tools/emalloc.c"
# include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../tree/edge.c"
#endif

/*====================================================================*
 *   program constants;  
 *--------------------------------------------------------------------*/

#define ORDER_B_INVERT (1 << 0)
#define ORDER_B_SYMBOL (1 << 1)
#define ORDER_B_STRUCT (1 << 2)
#define ORDER_B_ORDER  (1 << 3)
#define ORDER_B_LEVEL  (1 << 4)

/*====================================================================*
 *
 *   void print (signed indent, NODE * node, flag_t flags);
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void print (signed indent, NODE * node, flag_t flags) 

{ 
	if (_anyset (flags, ORDER_B_ORDER)) 
	{ 
		printf ("%03d ", node->index); 
	} 
	if (_anyset (flags, ORDER_B_LEVEL)) 
	{ 
		printf ("%03d ", node->level); 
	} 
	while (indent-- > 0) 
	{ 
		printf ("\t"); 
	} 
	printf ("%s\n", node->title); 
	return; 
} 

/*====================================================================*
 *   
 *   void traverse (NODE * node, flags_t flags);
 *
 *   traverse nodes using depth first search; increment order and
 *   level postorder; print nodes postorder as an inventory; test
 *   for circular reference preorder and terminate program; 
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void traverse (NODE * node, flag_t flags) 

{ 
	extern NODES nodes; 
	extern EDGES edges; 
	size_t index; 
	if (node->index) 
	{ 
		return; 
	} 
	if (node->level) 
	{ 
		return; 
	} 
	node->index = 1; 
	for (index = 0; index < edges.count; index++) 
	{ 
		EDGE * edge = edges.table [index]; 
		if (edge->source != node) 
		{ 
			continue; 
		} 
		traverse (edge->target, flags); 
		if (node->level < edge->target->level) 
		{ 
			node->level = edge->target->level; 
		} 
	} 
	nodes.order++; 
	node->level++; 
	node->index = nodes.order; 
	if (_anyset (flags, ORDER_B_SYMBOL)) 
	{ 
		print (0, node, flags); 
	} 
	return; 
} 

/*====================================================================*
 *   
 *   void organize (NODE * node, flags_t flags);
 *
 *   traverse nodes using depth first search; print nodes preorder
 *   as an outline;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void organize (NODE * node, flag_t flags) 

{ 
	extern EDGES edges; 
	static signed margin = 0; 
	NODE * temp; 
	size_t index; 
	if (_anyset (flags, ORDER_B_STRUCT)) 
	{ 
		print (margin, node, flags); 
	} 
	node->node = nodes.node; 
	nodes.node = node; 
	for (temp = node->node; temp; temp = temp->node) 
	{ 
		if (temp == node) 
		{ 
			extern char const * program_name; 
			fprintf (stderr, "%s: ", program_name); 
			fprintf (stderr, "cyclic reference: "); 
			fprintf (stderr, "%s:", temp->title); 
			for (temp = node->node; temp != node; temp = temp->node) 
			{ 
				fprintf (stderr, "%s:", temp->title); 
			} 
			fprintf (stderr, "%s;\n", temp->title); 
			return; 
		} 
	} 
	margin++; 
	for (index = 0; index < edges.count; index++) 
	{ 
		EDGE * edge = edges.table [index]; 
		if (edge->target == node) 
		{ 
			organize (edge->source, flags); 
		} 
	} 
	margin--; 
	nodes.node = node->node; 
	node->node = (NODE *)(0); 
	return; 
} 

/*====================================================================*
 *   
 *   void discover (flag_t flags);
 *
 *   walk the node list and traverse neighboring nodes;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void discover (flag_t flags) 

{ 
	extern NODES nodes; 
	size_t index; 
	for (index = 0; index < nodes.count; index++) 
	{ 
		NODE * node = nodes.table [index]; 
		traverse (node, flags); 
	} 
	for (index = 0; index < nodes.count; index++) 
	{ 
		NODE * node = nodes.table [index]; 
		if (node->level == 1) 
		{ 
			organize (node, flags); 
		} 
	} 
	return; 
} 

/*====================================================================*
 *
 *   int main (int argc, char const * argv[]);
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
		"loptx", 
		PUTOPTV_S_DIVINE, 
		"topological sort program", 
		"l\tprint level", 
		"o\tprint order", 
		"p\tprint names", 
		"t\tprint nodes", 
		"x\texchange order", 
		(char const *) (0)
	}; 
	flag_t flags = (flag_t)(0); 
	signed c; 
	while (~ (c = getoptv (argc, argv, optv))) 
	{ 
		switch (c) 
		{ 
		case 'l': 
			_setbits (flags, ORDER_B_LEVEL); 
			break; 
		case 'o': 
			_setbits (flags, ORDER_B_ORDER); 
			break; 
		case 'p': 
			_setbits (flags, ORDER_B_SYMBOL); 
			_clrbits (flags, ORDER_B_STRUCT); 
			break; 
		case 't': 
			_setbits (flags, ORDER_B_STRUCT); 
			_clrbits (flags, ORDER_B_SYMBOL); 
			break; 
		case 'x': 
			_setbits (flags, ORDER_B_INVERT); 
			break; 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 
	graphinit (); 
	if (!argc) 
	{ 
		populate (flags & ORDER_B_INVERT); 
	} 
	while ((argc) && (* argv)) 
	{ 
		if (efreopen (* argv, "rb", stdin)) 
		{ 
			populate (flags & ORDER_B_INVERT); 
		} 
		argc--; 
		argv++; 
	} 
	discover (flags); 
	graphfree (); 
	return (0); 
} 

