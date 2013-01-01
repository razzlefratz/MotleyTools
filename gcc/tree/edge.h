/*====================================================================*
 *
 *   edge.h - topological sorting definitions and declarations;
 *
 *.  Motley Tools by Charles Maier
 *:  compiled for debian gnu/linux environment using gcc 2.95 compiler;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef EDGE_HEADER
#define EDGE_HEADER

/*====================================================================*
 *   variables;
 *--------------------------------------------------------------------*/

typedef struct _node_ 

{
	struct _node_ * node;
	char const * title;
	signed value;
	signed level;
	signed index;
}

NODE;
typedef struct _nodes_ 

{
	NODE ** table;
	NODE * node;
	size_t block;
	size_t limit;
	size_t count;
	size_t index;
	size_t order;
}

NODES;
typedef struct _edge_ 

{
	NODE * source;
	NODE * target;
	char const * title;
	signed value;
}

EDGE;
typedef struct _edges_ 

{
	EDGE ** table;
	EDGE * edge;
	size_t block;
	size_t limit;
	size_t count;
	size_t index;
}

EDGES;

/*====================================================================*
 *   variables;
 *--------------------------------------------------------------------*/

extern NODES nodes;
extern EDGES edges;

/*====================================================================*
 *   function;   
 *--------------------------------------------------------------------*/

void graphinit ();
void graphfree ();
NODE * addnode (char const * title);
EDGE * addedge (char const * title1, char const * title2);
void populate (bool invert);

/*====================================================================*
 * end definitions;
 *--------------------------------------------------------------------*/

#endif

