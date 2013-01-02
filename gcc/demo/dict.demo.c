/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#include "../tools/tools.h"
#include "../tools/chars.h"
#include "../clang/clang.h"
#include "../dict/dict.h"
#include "../tree/tree.h"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#include "../dict/dictdefine.c"
#include "../dict/dictlookup.c"
#include "../dict/dictrevert.c"
#include "../dict/dictreport.c"
#include "../tools/emalloc.c"
#include "../sv/sv_cproc.c"
#include "../strlib/svindex.c"

int c;

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

TREE * define (TREE * tree) 

{
	char symbol [_MAXTOKEN];
	char string [_MAXTOKEN];
	char * sp,
	* cp;
	do 
	{
		c = getc (stdin);
	}
	while (isspace (c));
	for (sp = symbol; isalpha (c); c = getc (stdin)) 
	{
		* sp++ = c;
		* sp = (char) (0);
	}
	switch (svindex (symbol, sv_cproc, CPROC_O_NULL, strcmp)) 
	{
	case CPROC_O_DEFINE:
		while (isblank (c)) 
		{
			c = getc (stdin);
		}
		for (sp = symbol; isalnum (c) || (c == '_'); c = getc (stdin)) 
		{
			* sp++ = c;
		}
		* sp = (char) (0);
		while (isblank (c)) 
		{
			c = getc (stdin);
		}
		for (sp = cp = string; nobreak (c); c = getc (stdin)) 
		{
			* cp++ = c;
			if (!isblank (c)) 
			{
				sp = cp;
			}
		}
		* sp = (char) (0);
		tree = dictdefine (tree, symbol, string);
		break;
	case CPROC_O_UNDEF:
		while (isblank (c)) 
		{
			c = getc (stdin);
		}
		for (sp = symbol; isalnum (c) || (c == '_'); c = getc (stdin)) 
		{
			* sp++ = c;
		}
		* sp = (char) (0);
		tree = dictdefine (tree, symbol, string);
		break;
	default:
		break;
	}
	while (nobreak (c)) 
	{
		c = getc (stdin);
	}
	return (tree);
}


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const *argv []) 

{
	TREE * tree = (TREE *) (0);
	while ((c = getc (stdin)) != EOF) 
	{
		switch (c) 
		{
		case '#':
			tree = define (tree);
			break;
		default:
			break;
		}
	}
	dictreport (tree);
	return (0);
}

