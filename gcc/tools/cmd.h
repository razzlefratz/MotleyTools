/*====================================================================*
 *
 *   cmd.h - command definitions and declarations;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 2005 by Charles Maier Associates for internal use;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CMD_HEADER
#define CMD_HEADER

/*====================================================================*
 *   constants;
 *--------------------------------------------------------------------*/

#define CMD_FORMAT "%s: Found '%c' but expected '%c'.\n", __FUNCTION__
#define CMD_INDENT "   "

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

TREE * CMDLine ();
signed CMDRead ();
void CMDTree (TREE *);
void CMDFree (TREE *);

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#endif



