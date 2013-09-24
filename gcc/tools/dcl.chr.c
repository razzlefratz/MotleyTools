/*====================================================================*
 *
 *   dcl.chr.c - character based command line parser;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef DCL_CHR_SOURCE
#define DCL_CHR_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

char c;

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
 *   name := DIGIT
 *   name := <name> '_'
 *   name := <name> LETTER
 *   name := <name> DIGIT 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static TREE * DCLName()

{
	extern char c;
	TREE * name = NEW(TREE);
	char buffer[1024];
	char * string = buffer;
	while (isspace(c))
	{
		c = getc(stdin);
	}
	if (isalnum(c) || (c == '_'))
	{
		do 
		{
			* string++ = c;
			c = getc(stdin);
		}
		while (isalnum(c) || (c == '_'));
	}
	* string++ = (char) (0);
	name->name = (char *) (emalloc(string - buffer));
	name->one = (TREE *) (0);
	name->two = (TREE *) (0);
	return (name);
}

/*====================================================================*
 *
 *   TREE * DCLText ();
 *
 *   text := <quote>chars<quote)
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static TREE * DCLText(char quote)

{
	extern char c;
	TREE * text = NEW(TREE);
	char buffer[1024];
	char * string = buffer;
	while ((c != quote) && (c != EOF))
	{
		if (c == '\\')
		{
			c = getc(stdin);
			if (c == EOF)
			{
				break;
			}
		}
		* string++ = c;
		c = getc(stdin);
	}
	* string = (char) (0);
	text->name = strdup(buffer);
	text->one = (TREE *) (0);
	text->two = (TREE *) (0);
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

static TREE * DCLList(char comma, TREE * func())

{
	extern char c;
	TREE * list = func();
	TREE * item = list;
	while (c != EOF)
	{
		while (isspace(c))
		{
			c = getc(stdin);
		}
		if (c == comma)
		{
			c = getc(stdin);
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
	extern char c;
	TREE * item;
	while (isspace(c))
	{
		c = getc(stdin);
	}
	if (c == '(')
	{
		c = getc(stdin);
		item = DCLList(COMMA, DCLItem);
		if (c != ')')
		{
			error (1, 0, "Have '%c' but need '%c'", c, ')');
		}
		c = getc(stdin);
		return (item);
	}
	if (c == '[')
	{
		c = getc(stdin);
		item = DCLList(COLON, DCLItem);
		if (c != ']')
		{
			error (1, 0, "Have '%c' but need '%c'", c, ']');
		}
		c = getc(stdin);
		return (item);
	}
	if (c == '{')
	{
		c = getc(stdin);
		item = DCLList(BREAK, DCLItem);
		if (c != '}')
		{
			error (1, 0, "Have '%c' but need '%c'", c, '}');
		}
		c = getc(stdin);
		return (item);
	}
	if (c == QUOTE)
	{
		c = getc(stdin);
		item = DCLText(c);
		if (c != QUOTE)
		{
			error (1, 0, "Have '%c' but need '%c'", c, QUOTE);
		}
		c = getc(stdin);
		return (item);
	}
	if (c == APOST)
	{
		c = getc(stdin);
		item = DCLText(c);
		if (c != APOST)
		{
			error (1, 0, "Have '%c' but need '%c'", c, APOST);
		}
		c = getc(stdin);
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
	extern char c;
	TREE * term = DCLName();
	while (isspace(c))
	{
		c = getc(stdin);
	}
	if (c == '(')
	{
		c = getc(stdin);
		term->two = DCLList(COMMA, DCLItem);
		if (c != ')')
		{
			error (1, 0, "Have '%c' but need '%c'", c, ')');
		}
		c = getc(stdin);
		return (term);
	}
	if (c == EQUAL)
	{
		c = getc(stdin);
		term->two = DCLItem();
		return (term);
	}
	if (c == COLON)
	{
		c = getc(stdin);
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
	extern char c;
	TREE * line = DCLTerm();
	TREE * term = line;
	while (c != EOF)
	{
		while (isspace(c))
		{
			c = getc(stdin);
		}
		if (c == SLASH)
		{
			c = getc(stdin);
			term->two = DCLList(SLASH, DCLTerm);
			continue;
		}
		if (isalnum(c))
		{
			term->one = DCLTerm();
			term = term->one;
			continue;
		}
		break;
	}
	return (line);
}

/*====================================================================*
 *
 *   void DCLTree (TREE *node, unsigned level);
 *   
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
		free (temp->name);
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
#include <stdlib.h>
#include "../tools/emalloc.c"

char const * program_name;
int main(int argc, char * argv[])

{
	extern char c;
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
 *   
 *--------------------------------------------------------------------*/

#endif



