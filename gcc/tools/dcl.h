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
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tree/tree.h"

/*====================================================================*
 *   constants;
 *--------------------------------------------------------------------*/

#define COMMA ','
#define BREAK ';'
#define COLON ':'
#define SLASH '/'
#define EQUAL '='
#define QUOTE '\"'
#define APOST '\''

/*====================================================================*
 *   functions;
 *--------------------------------------------------------------------*/

TREE * DCLLine ();
void DCLTree (TREE * node);
void DCLFree (TREE * node);
void DCLInit ();
signed cgetc (signed fd);

#if 0

TREE *DCLName ();
TREE *DCLText (char c);
TREE *DCLList (char c, TREE * func ());
TREE *DCLItem ();
TREE *DCLTerm ();

#endif

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#endif

