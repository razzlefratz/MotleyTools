/*====================================================================*
 *
 *   tree.h - binary tree definitions and declarations;
 *
 *.  Motley Tools by Charles Maier
 *:  compiled for debian gnu/linux environment using gcc 2.95 compiler;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef TREE_HEADER
#define TREE_HEADER

/*====================================================================*
 *   custom header files;  
 *--------------------------------------------------------------------*/

#include <unistd.h>

/*====================================================================*
 *   declare datatypes;    
 *--------------------------------------------------------------------*/

typedef struct tree 

{
	struct tree * one;
	struct tree * two;
	struct tree * sub;
	void * name;
	void * data;
	size_t size;
}

TREE;

/*====================================================================*
 *   declare functions;
 *--------------------------------------------------------------------*/

TREE * savenode (TREE * node, void *name, int comp (void const *, void const *), void *init, void *make (void *, void *), void *data, void *edit (void *, void *));
TREE * findnode (TREE * node, void const *name, int comp (void const *, void const *));
TREE * editnode (TREE * node, void const *name, void *data, void *func (void *, void *));
TREE * freenode (TREE * node, void *data, void *func (void *, void *));
TREE * eventree (TREE * node);
void preorder (TREE * node, void *data, void func (TREE *, void *));
void postorder (TREE * node, void *data, void func (TREE *, void *));
void inorder (TREE * node, void *data, void func (TREE *, void *));
unsigned treesize (TREE * node);

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

TREE * termdefine (TREE *node, char const *name, char const * text, int comp (char const *, char const *));
char const * termlookup (TREE * node, char const *name, int comp (char const *, char const *));
void termreport (TREE *node, char const * format);

/*====================================================================*
 * end definitions;
 *--------------------------------------------------------------------*/

#endif

