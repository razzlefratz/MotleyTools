/*====================================================================*
 *
 *   edge.c - directed edge functions;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef EDGE_SOURCE
#define EDGE_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <memory.h>

#include "../tools/types.h"
#include "../tools/sizes.h"
#include "../tools/chars.h"
#include "../tools/memory.h"
#include "../tree/edge.h"

#define MAX_NODES _LISTSIZE
#define MAX_EDGES _LISTSIZE

NODES nodes = 

{
	(NODE **) (0),
	(NODE *) (0),
	(size_t) (0),
	(size_t) (0),
	(size_t) (0),
	(size_t) (0),
	(size_t) (0)
};

EDGES edges = 

{
	(EDGE **) (0),
	(EDGE *) (0),
	(size_t) (0),
	(size_t) (0),
	(size_t) (0),
	(size_t) (0)
};


/*====================================================================*
 *   
 *   void graphinit ();
 *
 *   initialize struct _nodes_ nodes and struct _edges_ edges by
 *   allocating tables and setting table management variables;
 *
 *   collectively, these two structures are capable of defining a
 *   directed graph;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void graphinit () 

{
	extern struct _nodes_ nodes;
	extern struct _edges_ edges;
	nodes.table = (NODE **) (emalloc (sizeof (NODE) * MAX_NODES));
	edges.table = (EDGE **) (emalloc (sizeof (EDGE) * MAX_EDGES));
	nodes.limit = nodes.block = MAX_NODES;
	edges.limit = edges.block = MAX_EDGES;
	nodes.count = nodes.index = 0;
	edges.count = edges.index = 0;
	return;
}


/*====================================================================*
 *   
 *   void graphfree ();
 *
 *   release memory allocated to struct _node_ nodes and struct
 *   _edge_ edges;
 *
 *   collectively, these two structures are capable of defining a
 *   directed graph;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void graphfree () 

{
	extern struct _nodes_ nodes;
	extern struct _edges_ edges;
	size_t index;
	for (index = 0; index < nodes.count; index++) 
	{
		NODE *node = nodes.table [index];
		if (node) 
		{
			free ((char *) (node->title));
			memset (node, 0, sizeof (NODE));
			free (node);
		}
	}
	for (index = 0; index < edges.count; index++) 
	{
		EDGE *edge = edges.table [index];
		if (edge) 
		{
			free ((char *) (edge->title));
			memset (edge, 0, sizeof (EDGE));
			free (edge);
		}
	}
	free (nodes.table);
	free (edges.table);
	memset (&nodes, 0, sizeof (nodes));
	memset (&edges, 0, sizeof (edges));
	return;
}


/*====================================================================*
 *   
 *   NODE * addnode (char const * title);
 *
 *   search the node table for the named node; add the node to the
 *   table if missing; expand the table as needed, return the node 
 *   address;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

NODE * addnode (char const * title) 

{
	extern struct _nodes_ nodes;
	for (nodes.index = 0; nodes.index < nodes.count; nodes.index++) 
	{
		NODE * node = nodes.table [nodes.index];
		if (!strcmp (node->title, title)) 
		{
			return (node);
		}
	}
	if (nodes.count >= nodes.limit) 
	{
		nodes.limit = nodes.limit + nodes.block;
		nodes.block = nodes.limit - nodes.block;
		nodes.table = (NODE **) (erealloc (nodes.table, nodes.limit * sizeof (NODE)));
	}
	NODE * node = nodes.table [nodes.count++] = NEW (NODE);
	memset (node, 0, sizeof (NODE));
	node->title = strdup (title);
	return (node);
}


/*====================================================================*
 *   
 *   EDGE * addedge (char const * sourcename, char const * targetname);
 *
 *   search the edge table for the named edge; add the edge to the
 *   table if missing; expand the table as needed; return the edge 
 *   address; we make an exception here when the source and target
 *   node are the same in order to streamline function organize;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

EDGE * addedge (char const * sourcename, char const * targetname) 

{
	extern struct _edges_ edges;
	struct _node_ *source = addnode (sourcename);
	struct _node_ *target = addnode (targetname);
	if (source == target) 
	{
		return ((EDGE *)(0));
	}
	for (edges.index = 0; edges.index < edges.count; edges.index++) 
	{
		EDGE * edge = edges.table [edges.index];
		if (edge->source != source) 
		{
			continue;
		}
		if (edge->target != target) 
		{
			continue;
		}
		return (edge);
	}
	if (edges.count >= edges.limit) 
	{
		edges.limit = edges.limit + edges.block;
		edges.block = edges.limit - edges.block;
		edges.table = (EDGE **) (erealloc (edges.table, sizeof (EDGE) * (edges.limit)));
	}
	EDGE * edge = edges.table [edges.count++] = NEW (EDGE);
	memset (edge, 0, sizeof (EDGE));
	edge->source = source;
	edge->target = target;
	return (edge);
}


/*====================================================================*
 *
 *   void populate (flag_t flags);
 *
 *   read stdin as a series of directed edges connecting named end
 *   points; add the edges to an edge list; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void populate (bool invert) 

{
	char source [TEXTLINE_MAX];
	char target [TEXTLINE_MAX];
	signed c = getc (stdin);
	while (c != EOF) 
	{
		char * sp = target;
		while (isspace (c)) 
		{
			c = getc (stdin);
		}
		if ((c == '#') || (c == ';')) 
		{
			do 
			{
				c = getc (stdin);
			}
			while ((c !='\n') && (c != EOF));
			continue;
		}
		while ((c != ',') && (c != ':') && (c != ';') && (c != '\n') && (c != EOF)) 
		{
			*sp++ = (char) (c);
			c = getc (stdin);
		}
		*sp = (char) (0);
		while (isblank (c)) 
		{
			c = getc (stdin);
		}
		if ((c == ',') || (c == ':')) 
		{
			c = getc (stdin);
		}
		while (isblank (c)) 
		{
			c = getc (stdin);
		}
		sp = source;
		while ((c != ';') && (c != '\n') && (c != EOF)) 
		{
			*sp++ = (char) (c);
			c = getc (stdin);
		}
		*sp = (char) (0);
		while (isblank (c)) 
		{
			c = getc (stdin);
		}
		if (c == ';') 
		{
			c = getc (stdin);
		}
		while (isspace (c)) 
		{
			c = getc (stdin);
		}
		if (invert) 
		{
			addedge (target, source);
		}
		else 
		{
			addedge (source, target);
		}
	}
	return;
}


#endif

