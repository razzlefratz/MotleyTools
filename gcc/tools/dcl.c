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
#include <unistd.h>
#include <libgen.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/dcl.h"
#include "../tools/error.h"

/*====================================================================*
 *   variables;
 *--------------------------------------------------------------------*/

static const char * format = "Found '%c' but expected '%c'\n";
static const char * indent = "   ";
static char buffer [1024];
static char * string = buffer;
char c = '\n';

/*====================================================================*
 *   functions;
 *--------------------------------------------------------------------*/

static TREE * DCLName ();
static TREE * DCLText (char c);
static TREE * DCLList (char c, TREE * item ());
static TREE * DCLItem ();
static TREE * DCLTerm ();

/*====================================================================*
 *
 *   signed DCLRead ();
 *
 *   return next character from stdin, normally the console; print a
 *   prompt when stdin is a tty device;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed DCLRead ()

{
	extern char const * program_name;
	extern char c;
	if (isatty(STDIN_FILENO) && (c == '\n'))
	{
		write (STDIN_FILENO, program_name, strlen(program_name));
		write (STDIN_FILENO, ": ", 2);
	}
	if (read(STDIN_FILENO, & c, sizeof(c)) == sizeof(c))
	{
		return (c);
	}
	return (EOF);
}

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
	TREE * node = malloc (sizeof (* node));
	node->next = (TREE *) (0);
	node->list = (TREE *) (0);
	node->name = string;
	while (isspace (c))
	{
		c = DCLRead ();
	}
	if (isalnum (c))
	{
		do 
		{
			* string ++ = (char) (c);
			c = DCLRead ();
		}
		while (isalnum (c) || (c == '.') || (c == ':') || (c == '_'));
	}
	* string ++ = (char) (0);
	return (node);
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
	extern char const * format;
	TREE * node = malloc (sizeof (* node));
	node->name = string;
	node->next = (TREE *) (0);
	node->list = (TREE *) (0);
	while ((c != quote) && (c != EOF))
	{
		if (c == '\\')
		{
			* string ++ = (char) (c);
			c = DCLRead ();
			if (c == EOF)
			{
				error (1, 0, format, c, quote);
			}
		}
		* string ++ = (char) (c);
		c = DCLRead ();
	}
	* string ++ = (char) (0);
	return (node);
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

TREE * DCLList (char comma, TREE * item ())

{
	extern char c;
	TREE * list = item ();
	TREE * node = list;
	while (c != EOF)
	{
		while (isspace (c))
		{
			c = DCLRead ();
		}
		if (c == comma)
		{
			c = DCLRead ();
			node->next = item ();
			node = node->next;
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
	extern char const * format;
	TREE * item;
	while (isspace (c))
	{
		c = DCLRead ();
	}
	if (c == '(')
	{
		c = DCLRead ();
		item = DCLList (',', DCLItem);
		if (c != ')')
		{
			error (1, 0, format, c, ')');
		}
		c = DCLRead ();
		return (item);
	}
	if (c == '[')
	{
		c = DCLRead ();
		item = DCLList (':', DCLItem);
		if (c != ']')
		{
			error (1, 0, format, c, ']');
		}
		c = DCLRead ();
		return (item);
	}
	if (c == '{')
	{
		c = DCLRead ();
		item = DCLList (';', DCLItem);
		if (c != '}')
		{
			error (1, 0, format, c, '}');
		}
		c = DCLRead ();
		return (item);
	}
	if (c == '\"')
	{
		c = DCLRead ();
		item = DCLText ('\"');
		if (c != '\"')
		{
			error (1, 0, format, c, '\"');
		}
		c = DCLRead ();
		return (item);
	}
	if (c == '\'')
	{
		c = DCLRead ();
		item = DCLText ('\'');
		if (c != '\'')
		{
			error (1, 0, format, c, '\'');
		}
		c = DCLRead ();
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
	extern char const * format;
	TREE * term = DCLName ();
	while (isspace (c))
	{
		c = DCLRead ();
	}
	if (c == '(')
	{
		c = DCLRead ();
		term->list = DCLList (',', DCLItem);
		if (c != ')')
		{
			error (1, 0, format, c, ')');
		}
		c = DCLRead ();
		return (term);
	}
	if (c == '=')
	{
		c = DCLRead ();
		term->list = DCLItem ();
		return (term);
	}
	if (c == ':')
	{
		c = DCLRead ();
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
			c = DCLRead ();
		}
		if (c == '/')
		{
			c = DCLRead ();
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
	extern const char * indent;
	static unsigned level = 0;
	static unsigned count = 0;
	level++;
	while (node)
	{
		for (count = 1; count < level; count ++)
		{
			printf("%s", indent);
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
		TREE * item = node;
		node = node->next;
		DCLFree (item->list);
		memset (item, 0, sizeof (* item));
		free (item);
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

char const * program_name = "";

int main (int argc, char * argv [])

{
	extern char c;
	extern char const * program_name;
	extern char const * format;
	static char const * optv [] =
	{
		"example command line program",
		"[< stdin] [> stdout]",
		"",
		(char const *) (0)
	};
	TREE * node = (TREE *) (0);
	program_name = basename (* argv);
	optind = 1;
	opterr = 1;
	while (~ (c = getopt (argc, argv, optv [2])))
	{
		switch (c)
		{
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	while (~ (c = DCLRead ()))
	{
		node = DCLLine ();
		if ((c != ';') && (c != EOF))
		{
			error (1, 0, format, c, ';');
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



