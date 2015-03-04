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

#include "../tools/memory.h"
#include "../tools/error.h"
#include "../tools/dcl.h"

/*====================================================================*
 *   variables;
 *--------------------------------------------------------------------*/

static char buffer [1024];
static char * string = buffer;
static char const * format = "Found '%c' when expecting '%c'\n";
static char const * indent = "   ";
static char c;

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

static TREE * DCLName ()

{
	extern char c;
	TREE * name = NEW (TREE);
	while (isspace (c))
	{
		c = getc (stdin);
	}
	if (isalnum (c) || (c == '_'))
	{
		do 
		{
			* string++ = c;
			c = getc (stdin);
		}
		while (isalnum (c) || (c == '_'));
	}
	* string++ = (char) (0);
	name->name = (char *) (emalloc (string - buffer));
	name->next = (TREE *) (0);
	name->list = (TREE *) (0);
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

static TREE * DCLText (char quote)

{
	extern char c;
	TREE * text = NEW (TREE);
	while ((c != quote) && (c != EOF))
	{
		if (c == '\\')
		{
			c = getc (stdin);
			if (c == EOF)
			{
				break;
			}
		}
		* string++ = c;
		c = getc (stdin);
	}
	* string = (char) (0);
	text->name = strdup (buffer);
	text->next = (TREE *) (0);
	text->list = (TREE *) (0);
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

static TREE * DCLList (char comma, TREE * func ())

{
	extern char c;
	TREE * list = func ();
	TREE * item = list;
	while (c != EOF)
	{
		while (isspace (c))
		{
			c = getc (stdin);
		}
		if (c == comma)
		{
			c = getc (stdin);
			item->next = func ();
			item = item->next;
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

static TREE * DCLItem ()

{
	extern char c;
	extern char const * format;
	TREE * item;
	while (isspace (c))
	{
		c = getc (stdin);
	}
	if (c == '(')
	{
		c = getc (stdin);
		item = DCLList (',', DCLItem);
		if (c != ')')
		{
			error (1, 0, format, c, ')');
		}
		c = getc (stdin);
		return (item);
	}
	if (c == '[')
	{
		c = getc (stdin);
		item = DCLList (':', DCLItem);
		if (c != ']')
		{
			error (1, 0, format, c, ']');

		}
		c = getc (stdin);
		return (item);
	}
	if (c == '{')
	{
		c = getc (stdin);
		item = DCLList (';', DCLItem);
		if (c != '}')
		{
			error (1, 0, format, c, '}');
		}
		c = getc (stdin);
		return (item);
	}
	if (c == '\"')
	{
		c = getc (stdin);
		item = DCLText (c);
		if (c != '\"')
		{
			error (1, 0, format, c, '\"');
		}
		c = getc (stdin);
		return (item);
	}
	if (c == '\'')
	{
		c = getc (stdin);
		item = DCLText (c);
		if (c != '\'')
		{
			error (1, 0, format, c, '\'');
		}
		c = getc (stdin);
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

static TREE * DCLTerm ()

{
	extern char c;
	extern char const * format;
	TREE * term = DCLName ();
	while (isspace (c))
	{
		c = getc (stdin);
	}
	if (c == '(')
	{
		c = getc (stdin);
		term->list = DCLList (',', DCLItem);
		if (c != ')')
		{
			error (1, 0, format, c, ')');
		}
		c = getc (stdin);
		return (term);
	}
	if (c == '=')
	{
		c = getc (stdin);
		term->list = DCLItem ();
		return (term);
	}
	if (c == ':')
	{
		c = getc (stdin);
		term->list = DCLItem ();
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
			c = getc (stdin);
		}
		if (c == '/')
		{
			c = getc (stdin);
			term->list = DCLList ('/', DCLTerm);
			continue;
		}
		if (isalnum (c))
		{
			term->next = DCLTerm ();
			term = term->next;
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

void DCLTree (TREE * node)

{
	static unsigned level = 0;
	static unsigned count = 0;
	level++;
	while (node)
	{
		for (count = 1; count < level; count++)
		{
			printf ("%s", indent);
		}
		printf ("[%s]\n", node->name);
		DCLTree (node->list);
		node = node->next;
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
		node = node->next;
		DCLFree (temp->list);
		temp->next = (TREE *) (0);
		temp->list = (TREE *) (0);
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
int main (int argc, char * argv [])

{
	extern char c;
	extern char const * program_name;
	TREE * node = (TREE *) (0);
	program_name = * argv;
	while ((c = getc (stdin)) != EOF)
	{
		node = DCLLine ();
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



