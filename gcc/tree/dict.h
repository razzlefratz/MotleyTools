/*====================================================================*
 *
 *   dict.h - dictionary constant definitions and function declarations;
 *
 *.  Motley Tools by Charles Maier
 *:  compiled for debian gnu/linux environment using gcc 2.95 compiler;
 *;  Licensed under the Internet Software Consortium License
 *   charles_maier_assoc@msn.com;
 *
 *--------------------------------------------------------------------*/

#ifndef DICT_HEADER
#define DICT_HEADER

#include "../tree/tree.h"

/*====================================================================*
 * declare item structure
 *--------------------------------------------------------------------*/

TREE *dictdefine (TREE *node, char const *name, char const *text);
char *dictlookup (TREE *node, char const *name);
void dictrevert (TREE *node, char const *name);
void dictreport (TREE *node);

/*====================================================================*
 * end definitions;
 *--------------------------------------------------------------------*/

#endif

