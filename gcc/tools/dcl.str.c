/*====================================================================*
 *
 *   dcl.str.c - string based command line parser;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef DCL_STR_SOURCE
#define DCL_STR_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/dcl.h"
#include "../tools/memory.h"
#include "../tools/error.h"
#include "../tree/tree.h"

/*====================================================================*
 *   variables;
 *--------------------------------------------------------------------*/

static char * string = (char *) (0);

// static signed c;

/*====================================================================*
 *   functions;
 *--------------------------------------------------------------------*/

static TREE * DCLName();
static TREE * DCLText(char c);
static TREE * DCLList(char c, TREE * func());
static TREE * DCLItem();
static TREE * DCLTerm();

/*====================================================================*
 *
 *   TREE * DCLName ();
 *   
 *   name := '_' 
 *   name := LETTER
 *   name := <name> '_'
 *   name := <name> LETTER
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static TREE * DCLName()

{
	TREE * name = NEW(TREE);
	while (isspace(* string))
	{
		* string++ = (char) (0);
	}
	name->name = string;
	name->one = (TREE *) (0);
	name->two = (TREE *) (0);
	if (isalnum(* string) || (* string == '_'))
	{
		do 
		{
			string++;
		}
		while (isalnum(* string) || (* string == '_'));
	}
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

static TREE * DCLText(char c)

{
	TREE * text = NEW(TREE);
	text->one = (TREE *) (0);
	text->two = (TREE *) (0);
	text->name = string;
	while (* string != c)
	{
		if (* string == '\\')
		{
			string++;
		}
		if (! * string)
		{
			error (1, 0, "Have '%s' but want '%c'", string, c);
		}
		string++;
	}
	* string++ = (char) (0);
	return (text);
}

/*====================================================================*
 *
 *   TREE *DCLList (char comma, TREE * func ());
 *   
 *   list :== <item>
 *   list :== <list>,<item>
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static TREE * DCLList(char c, TREE * func())

{
	TREE * list = func();
	TREE * item = list;
	while (* string)
	{
		while (isspace(* string))
		{
			* string++ = (char) (0);
		}
		if (* string == c)
		{
			* string++ = (char) (0);
			item->one = func();
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

static TREE * DCLItem()

{
	TREE * item;
	while (isspace(* string))
	{
		* string++ = (char) (0);
	}
	if (* string == '(')
	{
		* string++ = (char) (0);
		item = DCLList(COMMA, DCLItem);
		if (* string != ')')
		{
			error (1, 0, "Have '%s' but need ')'", string);
		}
		* string++ = (char) (0);
		return (item);
	}
	if (* string == '[')
	{
		* string++ = (char) (0);
		item = DCLList(COLON, DCLItem);
		if (* string != ']')
		{
			error (1, 0, "Have '%s' but need ']'", string);
		}
		* string++ = (char) (0);
		return (item);
	}
	if (* string == '{')
	{
		* string++ = (char) (0);
		item = DCLList(BREAK, DCLItem);
		if (* string != '}')
		{
			error (1, 0, "Have '%s' but need ')'", string);
		}
		* string++ = (char) (0);
		return (item);
	}
	if (* string == QUOTE)
	{
		* string++ = (char)(0);
		item = DCLText(QUOTE);
		return (item);
	}
	if (* string == APOST)
	{
		* string++ = (char)(0);
		item = DCLText(APOST);
		return (item);
	}
	item = DCLTerm();
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

static TREE * DCLTerm()

{
	TREE * term = DCLName();
	while (isspace(* string))
	{
		* string++ = (char) (0);
	}
	if (* string == '(')
	{
		* string++ = (char) (0);
		term->two = DCLList(COMMA, DCLItem);
		if (* string != ')')
		{
			error (1, 0, "Have '%s' but need ')'", string);
		}
		* string++ = (char) (0);
		return (term);
	}
	if (* string == EQUAL)
	{
		* string++ = (char) (0);
		term->two = DCLItem();
		return (term);
	}
	if (* string == COLON)
	{
		* string++ = (char) (0);
		term->two = DCLItem();
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

TREE * DCLLine()

{
	TREE * line = DCLTerm();
	TREE * term = line;
	while (* string)
	{
		while (isspace(* string))
		{
			* string++ = (char) (0);
		}
		if (* string == SLASH)
		{
			* string++ = (char) (0);
			term->two = DCLList(SLASH, DCLTerm);
			continue;
		}
		if (isalnum(* string))
		{
			term->one = DCLTerm();
			term = term->one;
			continue;
		}
		break;
	}
	* string = (char) (0);
	return (line);
}

/*====================================================================*
 *
 *   void DCLTree (TREE *node);
 *
 *   print indented DCL tree on stdout;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void DCLTree(TREE * node)

{
	static unsigned level = 0;
	static unsigned count = 0;
	level++;
	while (node)
	{
		for (count = 1; count < level; count++)
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
 *   release memory allocated to DCL tree;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void DCLFree(TREE * node)

{
	while (node)
	{
		TREE * temp = node;
		node = node->one;
		DCLFree (temp->two);
		temp->one = (TREE *)(0);
		temp->two = (TREE *)(0);
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

#if 0
#include <stdio.h>
#include "../tools/error.c"
#include "../tools/emalloc.c"

char const * program_name;
int main(int argc, char * argv[])

{
	TREE * node = (TREE *) (0);
	program_name = * argv;
	while ((c = getc(stdin)) != EOF)
	{
		node = DCLLine();
		DCLTree (node);
		DCLFree (node);
	}
	return (0);
}

#endif

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#endif



