/*====================================================================*
 *
 *   depend.h - topological sorting definitions and declarations;
 *
 *.  Motley Tools by Charles Maier
 *:  compiled for debian gnu/linux environment using gcc 2.95 compiler;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef DEPEND_HEADER
#define DEPEND_HEADER

/*====================================================================*
 *   custom include files;
 *--------------------------------------------------------------------*/

#include "../link/link.h"
#include "../tree/tree.h"

/*====================================================================*
 *   extern variables;
 *--------------------------------------------------------------------*/

extern TREE *nodetree;
extern TREE *lastnode;
extern LINK *nodelist;
extern LINK *nodeitem;

/*====================================================================*
 *   function declarations;
 *--------------------------------------------------------------------*/

TREE *storenode (TREE * node, TREE * home, char const *name, void *data, int (*comp) (char const *, char const *));
TREE *fetchnode (TREE * node, char const *name, int (*comp) (char const *, char const *));
TREE *ordernode (TREE * node, char const *need, char const *feed, int (*comp) (char const *, char const *));

/*====================================================================*
 *   function declarations; 
 *--------------------------------------------------------------------*/

void enumerate (TREE * node);
void structure (TREE * node);
void component (TREE * node);

/*====================================================================*
 * end definitions;
 *--------------------------------------------------------------------*/

#endif

