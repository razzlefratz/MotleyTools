/*====================================================================*
 *
 *   dcl.c -                                  
 *
 *   copy one or more files to stdout; if no files are specified 
 *   then copy stdin to stdout;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef DCL_SOURCE
#define DCL_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <memory.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/dcl.h"
#include "../tools/memory.h"
#include "../tools/error.h"
#include "../linux/linux.h"
#include "../tree/tree.h"

/*====================================================================*
 *   variables;
 *--------------------------------------------------------------------*/

static char buffer [1024];
static char * string = buffer;
char c = (char) (0);

/*====================================================================*
 *   functions;
 *--------------------------------------------------------------------*/

static TREE * DCLName ();
static TREE * DCLText (char c);
static TREE * DCLList (char c, TREE * func ());
static TREE * DCLItem ();
static TREE * DCLTerm ();

/*====================================================================*
 *
 *   TREE * DCLName ();
 *   
 *   name := letter 
 *   name := digit 
 *   name := _
 *   name := name letter
 *   name := name digit
 *   name := name _
 *   name := name .
 *   name := name :
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

TREE * DCLName ()

{
	extern char c;
	TREE * name = NEW (TREE);
	name->name = string;
	name->one = (TREE *) (0);
	name->two = (TREE *) (0);
	while (isspace (c))
	{
		c = cgetc (STDIN_FILENO);
	}
	if (isalnum (c))
	{
		do 
		{
			* string ++ = (char) (c);
			c = cgetc (STDIN_FILENO);
		}
		while (isalnum (c) || (c == '.') || (c == ':') || (c == '_'));
	}
	* string ++ = (char) (0);
	return (name);
}

/*====================================================================*
 *
 *   TREE * DCLText ();
 *
 *   text := chars<quote>
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

TREE * DCLText (char quote)

{
	extern char c;
	TREE * text = NEW (TREE);
	text->name = string;
	text->one = (TREE *) (0);
	text->two = (TREE *) (0);
	while ((c != quote) && (c != EOF))
	{
		if (c == '\\')
		{
			* string ++ = (char) (c);
			c = cgetc (STDIN_FILENO);
			if (c == EOF)
			{
				error (1, 0, ERROR, c, quote);
			}
		}
		* string ++ = (char) (c);
		c = cgetc (STDIN_FILENO);
	}
	* string ++ = (char) (0);
	return (text);
}

/*====================================================================*
 *
 *   TREE *DCLList (char comma, TREE * item ());
 *   
 *   list :== <item>
 *   list :== <list>,<item>
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

TREE * DCLList (char comma, TREE * func ())

{
	extern char c;
	TREE * list = func ();
	TREE * item = list;
	while (c != EOF)
	{
		while (isspace (c))
		{
			c = cgetc (STDIN_FILENO);
		}
		if (c == comma)
		{
			c = cgetc (STDIN_FILENO);
			item->one = func ();
			item = item->one;
			continue;
		}
		break;
	}
	return (list);
}

/*====================================================================*
 *
 *   TREE * DCLItem ();
 *
 *   item :== (<list>)
 *   item :== [<list>]
 *   item :== {<list>}
 *   item :== "text"
 *   item :== 'text'
 *   item :== <term>
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

TREE * DCLItem ()

{
	extern char c;
	TREE * item;
	while (isspace (c))
	{
		c = cgetc (STDIN_FILENO);
	}
	if (c == '(')
	{
		c = cgetc (STDIN_FILENO);
		item = DCLList (COMMA, DCLItem);
		if (c != ')')
		{
			error (1, 0, ERROR, c, ')');
		}
		c = cgetc (STDIN_FILENO);
		return (item);
	}
	if (c == '[')
	{
		c = cgetc (STDIN_FILENO);
		item = DCLList (COLON, DCLItem);
		if (c != ']')
		{
			error (1, 0, ERROR, c, ']');
		}
		c = cgetc (STDIN_FILENO);
		return (item);
	}
	if (c == '{')
	{
		c = cgetc (STDIN_FILENO);
		item = DCLList (BREAK, DCLItem);
		if (c != '}')
		{
			error (1, 0, ERROR, c, '}');
		}
		c = cgetc (STDIN_FILENO);
		return (item);
	}
	if (c == '\"')
	{
		c = cgetc (STDIN_FILENO);
		item = DCLText (QUOTE);
		if (c != '\"')
		{
			error (1, 0, ERROR, c, '\"');
		}
		c = cgetc (STDIN_FILENO);
		return (item);
	}
	if (c == '\'')
	{
		c = cgetc (STDIN_FILENO);
		item = DCLText (APOST);
		if (c != '\'')
		{
			error (1, 0, ERROR, c, '\'');
		}
		c = cgetc (STDIN_FILENO);
		return (item);
	}
	item = DCLTerm ();
	return (item);
}

/*====================================================================*
 *
 *   TREE * DCLTerm ();
 *   
 *   term :== <name>
 *   term :== <name>(<list>)
 *   term :== <name>=<item>
 *   term :== <name>:<item>
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

TREE * DCLTerm ()

{
	extern char c;
	TREE * term = DCLName ();
	while (isspace (c))
	{
		c = cgetc (STDIN_FILENO);
	}
	if (c == '(')
	{
		c = cgetc (STDIN_FILENO);
		term->two = DCLList (COMMA, DCLItem);
		if (c != ')')
		{
			error (1, 0, ERROR, c, ')');
		}
		c = cgetc (STDIN_FILENO);
		return (term);
	}
	if (c == EQUAL)
	{
		c = cgetc (STDIN_FILENO);
		term->two = DCLItem ();
		return (term);
	}
	if (c == COLON)
	{
		c = cgetc (STDIN_FILENO);
		term->two = DCLItem ();
		return (term);
	}
	return (term);
}

/*====================================================================*
 *
 *   TREE * DCLLine ();
 *   
 *   line :== <term>
 *   line :== <line> <term>
 *   line :== <line>/<term>
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

TREE * DCLLine ()

{
	extern char c;
	TREE * line = DCLTerm ();
	TREE * term = line;
	while (c != EOF)
	{
		while (isspace (c))
		{
			c = cgetc (STDIN_FILENO);
		}
		if (c == SLASH)
		{
			c = cgetc (STDIN_FILENO);
			term->two = DCLList (SLASH, DCLTerm);
			continue;
		}
		if (isalnum (c))
		{
			term->one = DCLTerm ();
			term = term->one;
			continue;
		}
		break;
	}
	return (line);
}

/*=*
 *
void DCLInit ();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *-*/

void DCLInit ()

{
	string = buffer;
	return;
}

/*====================================================================*
 *
 *   void DCLTree (TREE *node);
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void DCLTree (TREE * node)

{
	static unsigned level = 0;
	static unsigned count = 0;
	level++;
	while (node)
	{
		for (count = 1; count < level; count ++)
		{
			putc (' ', stdout);
			putc (' ', stdout);
			putc (' ', stdout);
		}
		putc ('[', stdout);
		fputs ((char *) (node->name), stdout);
		putc (']', stdout);
		putc ('\n', stdout);
		DCLTree (node->two);
		node = node->one;
	}
	level--;
	return;
}

/*====================================================================*
 *
 *   void DCLFree (TREE * node);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void DCLFree (TREE * node)

{
	while (node)
	{
		TREE * temp = node;
		node = node->one;
		DCLFree (temp->two);
		memset (temp, 0, sizeof (TREE));
		free (temp);
	}
	return;
}

/*====================================================================*
 *
 *   int main (int argc, char * argv []);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#if 1
#include <stdio.h>

#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/emalloc.c"
#include "../tools/error.c"
#include "../tools/cgetc.c"

int main (int argc, char const * argv [])

{
	extern char c;
	static char const * optv [] =
	{
		"",
		PUTOPTV_S_FUNNEL,
		"example command line program",
		(char const *) (0)
	};
	TREE * node = (TREE *) (0);
	optind = 1;
	opterr = 1;
	while ((c = getoptv (argc, argv, optv)) != -1)
	{
		switch (c)
		{
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	while ((c = cgetc (STDIN_FILENO)) != EOF)
	{
		node = DCLLine ();
		if ((c != ';') && (c != EOF))
		{
			error (1, 0, ERROR, c, ';');
		}
		DCLTree (node);
		DCLFree (node);
	}
	return (0);
}

#endif

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#endif



