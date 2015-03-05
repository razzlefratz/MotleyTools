/*====================================================================*
 *
 *   cmd.c -                                  
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CMD_SOURCE
#define CMD_SOURCE

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

#include "../tools/cmd.h"
#include "../tools/error.h"

/*====================================================================*
 *   variables;
 *--------------------------------------------------------------------*/

static char buffer [2048];
static char * string = buffer;
static char c = '\n';

/*====================================================================*
 *   functions;
 *--------------------------------------------------------------------*/

static TREE * CMDName ();
static TREE * CMDText (char);
static TREE * CMDList (char, TREE * ());
static TREE * CMDItem ();
static TREE * CMDTerm ();

/*====================================================================*
 *
 *   signed CMDRead ();
 *
 *   return next character from stdin, normally the console; print a
 *   prompt when stdin is a tty device;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed CMDRead ()

{
	extern char c;
	extern char const * program_name;
	if (isatty (STDIN_FILENO) && (c == '\n'))
	{
		write (STDIN_FILENO, program_name, strlen (program_name));
		write (STDIN_FILENO, ": ", 2);
	}
	if (read (STDIN_FILENO, & c, sizeof (c)) != sizeof (c))
	{
		return (EOF);
	}
	if (!isatty (STDIN_FILENO))
	{
		write (STDERR_FILENO, &c, sizeof (c));
	}
	return (c);
}

/*====================================================================*
 *
 *   TREE * CMDName ();
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

TREE * CMDName ()

{
	extern char c;
	TREE * node = malloc (sizeof (* node));
	node->next = (TREE *) (0);
	node->list = (TREE *) (0);
	node->name = string;
	while (isspace (c))
	{
		c = CMDRead ();
	}
	if (isalpha (c) || (c == '_') || (c == '$'))
	{
		do { * string ++ = c; c = CMDRead (); } while (isalnum (c) || (c == '_') || (c == '-') || (c == '.'));
		* string ++ = (char) (0);
		return (node);
	}
	if (isdigit (c) || (c == '+') || (c == '-') || (c == '.'))
	{
		if (c == '0')
		{
			* string ++ = c;
			c = CMDRead ();
		}
		if ((c == 'x') || (c == 'X'))
		{
			do { * string ++ = c; c = CMDRead (); } while (isxdigit (c));
		}
		else
		{
			do { * string ++ = c; c = CMDRead (); } while (isdigit (c) || (c == '.') || (c == ':'));
		}
		* string ++ = (char) (0);
		return (node);
	}
	* string ++ = (char) (0);
	return (node);
}

/*====================================================================*
 *
 *   TREE * CMDText ();
 *
 *   text := chars<quote>
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

TREE * CMDText (char quote)

{
	extern char c;
	TREE * node = malloc (sizeof (* node));
	node->next = (TREE *) (0);
	node->list = (TREE *) (0);
	node->name = string;
	while ((c != quote) && (c != EOF))
	{
		if (c == '\\')
		{
			* string ++ = (char) (c);
			c = CMDRead ();
			if (c == EOF)
			{
				error (1, 0, CMD_FORMAT, c, quote);
			}
		}
		* string ++ = c;
		c = CMDRead ();
	}
	* string ++ = (char) (0);
	return (node);
}

/*====================================================================*
 *
 *   TREE *CMDList (char comma, TREE * item ());
 *   
 *   list :== <item>
 *   list :== <list>,<item>
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

TREE * CMDList (char comma, TREE * item ())

{
	extern char c;
	TREE * list = item ();
	TREE * node = list;
	while (c != EOF)
	{
		while (isspace (c))
		{
			c = CMDRead ();
		}
		if (c == comma)
		{
			c = CMDRead ();
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
 *   TREE * CMDItem ();
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

TREE * CMDItem ()

{
	extern char c;
	TREE * item;
	while (isspace (c))
	{
		c = CMDRead ();
	}
	if (c == '(')
	{
		c = CMDRead ();
		item = CMDList (',', CMDItem);
		if (c != ')')
		{
			error (1, 0, CMD_FORMAT, c, ')');
		}
		c = CMDRead ();
		return (item);
	}
	if (c == '[')
	{
		c = CMDRead ();
		item = CMDList (':', CMDItem);
		if (c != ']')
		{
			error (1, 0, CMD_FORMAT, c, ']');
		}
		c = CMDRead ();
		return (item);
	}
	if (c == '{')
	{
		c = CMDRead ();
		item = CMDList (';', CMDItem);
		if (c != '}')
		{
			error (1, 0, CMD_FORMAT, c, '}');
		}
		c = CMDRead ();
		return (item);
	}
	if (c == '\"')
	{
		c = CMDRead ();
		item = CMDText ('\"');
		if (c != '\"')
		{
			error (1, 0, CMD_FORMAT, c, '\"');
		}
		c = CMDRead ();
		return (item);
	}
	if (c == '\'')
	{
		c = CMDRead ();
		item = CMDText ('\'');
		if (c != '\'')
		{
			error (1, 0, CMD_FORMAT, c, '\'');
		}
		c = CMDRead ();
		return (item);
	}
	item = CMDTerm ();
	return (item);
}

/*====================================================================*
 *
 *   TREE * CMDTerm ();
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

TREE * CMDTerm ()

{
	extern char c;
	TREE * term = CMDName ();
	while (isspace (c))
	{
		c = CMDRead ();
	}
	if (c == '=')
	{
		c = CMDRead ();
		term->list = CMDItem ();
		return (term);
	}
	if (c == ':')
	{
		c = CMDRead ();
		term->list = CMDItem ();
		return (term);
	}
	if (c == '(')
	{
		c = CMDRead ();
		term->list = CMDList (',', CMDItem);
		if (c != ')')
		{
			error (1, 0, CMD_FORMAT, c, ')');
		}
		c = CMDRead ();
		return (term);
	}
	return (term);
}

/*====================================================================*
 *
 *   TREE * CMDLine ();
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

TREE * CMDLine ()

{
	extern char c;
	extern char buffer [];
	extern char * string;
	TREE * line = CMDTerm ();
	TREE * term = line;
	while (c != EOF)
	{
		while (isspace (c))
		{
			c = CMDRead ();
		}
		if (c == ';')
		{
			return (line);
		}
		if (c == '/')
		{
			c = CMDRead ();
			term->list = CMDList ('/', CMDTerm);
			continue;
		}
		if (isalnum (c))
		{
			term->next = CMDTerm ();
			term = term->next;
			continue;
		}
		break;
	}
	string = buffer;
	return (line);
}

/*====================================================================*
 *
 *   void CMDTree (TREE *node);
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void CMDTree (TREE * item)

{
	static unsigned level = 0;
	static unsigned count = 0;
	level++;
	while (item)
	{
		for (count = 1; count < level; count ++)
		{
			printf ("%s", CMD_INDENT);
		}
		printf ("[%s]\n", item->name);
		CMDTree (item->list);
		item = item->next;
	}
	level--;
	return;
}

/*====================================================================*
 *
 *   void CMDFree (TREE * node);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void CMDFree (TREE * list)

{
	while (list)
	{
		TREE * item = list;
		list = item->next;
		CMDFree (item->list);
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

#if 1
#include <stdio.h>
#include "../tools/error.c"

char const * program_name = "";
int main (int argc, char * argv [])

{
	extern char const * program_name;
	static char const * optv [] =
	{
		"example command line program",
		"[< stdin] [> stdout]",
		"",
		(char const *) (0)
	};
	signed c;
	optind = 1;
	opterr = 1;
	program_name = basename (* argv);
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
	while (~ (c = CMDRead ()))
	{
		TREE * node = CMDLine ();
		CMDTree (node);
		CMDFree (node);
	}
	return (0);
}

#endif

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#endif



