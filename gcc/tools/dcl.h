/*====================================================================*
 *
 *   dcl.h - command definitions and declarations;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 2005 by Charles Maier Associates for internal use;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef DCL_HEADER
#define DCL_HEADER

/*====================================================================*
 *   variables;
 *--------------------------------------------------------------------*/

typedef struct tree 

{
	struct tree * next;
	struct tree * list;
	char * name;
}

TREE;

/*====================================================================*
 *   functions;
 *--------------------------------------------------------------------*/

TREE * DCLLine ();
signed DCLRead ();
void DCLTree (TREE * node);
void DCLFree (TREE * node);

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#endif



