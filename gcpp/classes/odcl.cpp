/*====================================================================*
 *
 *   odcl.cpp -                                  
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oDCL_SOURCE
#define oDCL_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <unistd.h>
#include <cstdio>
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../GobiSampleCM/dcl.h"

/*====================================================================*
 *   variables;
 *--------------------------------------------------------------------*/

char odcl::buffer [1024];
char * odcl::string = buffer;
char const * odcl::format = "Found '%c' when expecting '%c'\n";
char const * odcl::indent = "   ";
signed c = (char) (0);

/*====================================================================*
 *
 *   int odcl::grab (int fd);
 *
 *   return next character from stdin, normally the console; print a
 *   prompt when stdin is a tty device;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

int odcl::grab ()

{
	extern char const * program_name;
	static char c = '\n';
	if (isatty (STDIN_FILENO) && (c == '\n'))
	{
		write (STDIN_FILENO, program_name, std::strlen (program_name));
		write (STDIN_FILENO, ": ", 2);
	}
	if (read (STDIN_FILENO, & c, sizeof (c)) == sizeof (c))
	{
		return (c);
	}
	if (isatty (STDIN_FILENO))
	{
		write (STDIN_FILENO, & c, sizeof (c));
	}
	return (EOF);
}

/*====================================================================*
 *
 *   void error (int code, errno_t error, char const * format, ...);
 *
 *   print an error message using variable argument list; prefix all
 *   messages with program_name; append strerror() message text when
 *   number is not non-zero; exit with status if status is non-zero;
 *
 *   included for compatibility with the GNU C library;
 *
 *--------------------------------------------------------------------*/

void odcl::error (int status, errno_t number, char const * format, ...)

{
	extern char const * program_name;
	if ((program_name) && (* program_name))
	{
		std::cerr << program_name << ": ";
	}
	if (number)
	{
		std::cerr << std::strerror (number) << ": ";
		errno = 0;
	}
	if ((format) && (* format))
	{
		va_list arglist;
		va_start (arglist, format);
		std::vfprintf (stderr, format, arglist);
		va_end (arglist);
	}
	std::cerr << std::endl;
	if (status)
	{
		std::exit (status);
	}
	return;
}

/*====================================================================*
 *
 *   TREE * odcl::name ();
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

TREE * odcl::name ()

{
	extern signed c;
	TREE * name = new TREE;
	name->next = (TREE *) (0);
	name->list = (TREE *) (0);
	name->name = string;
	while (std::isspace (c))
	{
		c = odcl::grab ();
	}
	if (std::isalnum (c))
	{
		do 
		{
			* string ++ = (char) (c);
			c = odcl::grab ();
		}
		while (std::isalnum (c) || (c == '.') || (c == ':') || (c == '_'));
	}
	* string ++ = (char) (0);
	return (name);
}

/*====================================================================*
 *
 *   TREE * text ();
 *
 *   text := <quote>chars<quote>
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

TREE * odcl::text (char quote)

{
	extern signed c;
	TREE * text = new TREE;
	text->next = (TREE *) (0);
	text->list = (TREE *) (0);
	text->name = string;
	while ((c != quote) && (c != EOF))
	{
		if (c == '\\')
		{
			* string ++ = (char) (c);
			c = odcl::grab ();
			if (c == EOF)
			{
				odcl::error (1, 0, odcl::format, c, quote);
			}
		}
		* string ++ = (char) (c);
		c = odcl::grab ();
	}
	* string ++ = (char) (0);
	return (text);
}

/*====================================================================*
 *
 *   TREE * list (char comma, TREE * item ());
 *   
 *   list :== <item>
 *   list :== <list>,<item>
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

TREE * odcl::list (char comma, TREE * item ())

{
	extern signed c;
	TREE * list = item ();
	TREE * node = list;
	while (c != EOF)
	{
		while (std::isspace (c))
		{
			c = odcl::grab ();
		}
		if (c == comma)
		{
			c = odcl::grab ();
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
 *   TREE * item ();
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

TREE * odcl::item ()

{
	extern signed c;
	TREE * item;
	while (std::isspace (c))
	{
		c = odcl::grab ();
	}
	if (c == '(')
	{
		c = odcl::grab ();
		item = odcl::list (',', odcl::item);
		if (c != ')')
		{
			odcl::error (1, 0, odcl::format, c, ')');
		}
		c = odcl::grab ();
		return (item);
	}
	if (c == '[')
	{
		c = odcl::grab ();
		item = odcl::list (':', odcl::item);
		if (c != ']')
		{
			odcl::error (1, 0, odcl::format, c, ']');
		}
		c = odcl::grab ();
		return (item);
	}
	if (c == '{')
	{
		c = odcl::grab ();
		item = odcl::list (';', odcl::item);
		if (c != '}')
		{
			odcl::error (1, 0, odcl::format, c, '}');
		}
		c = odcl::grab ();
		return (item);
	}
	if (c == '\"')
	{
		c = odcl::grab ();
		item = odcl::text ('\"');
		if (c != '\"')
		{
			odcl::error (1, 0, odcl::format, c, '\"');
		}
		c = odcl::grab ();
		return (item);
	}
	if (c == '\'')
	{
		c = odcl::grab ();
		item = odcl::text ('\'');
		if (c != '\'')
		{
			odcl::error (1, 0, odcl::format, c, '\'');
		}
		c = odcl::grab ();
		return (item);
	}
	item = odcl::term ();
	return (item);
}

/*====================================================================*
 *
 *   TREE * odcl::term ();
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

TREE * odcl::term ()

{
	extern signed c;
	TREE * term = odcl::name ();
	while (std::isspace (c))
	{
		c = odcl::grab ();
	}
	if (c == '(')
	{
		c = odcl::grab ();
		term->list = odcl::list (',', odcl::item);
		if (c != ')')
		{
			odcl::error (1, 0, odcl::format, c, ')');
		}
		c = odcl::grab ();
		return (term);
	}
	if (c == '=')
	{
		c = odcl::grab ();
		term->list = odcl::item ();
		return (term);
	}
	if (c == ':')
	{
		c = odcl::grab ();
		term->list = odcl::item ();
		return (term);
	}
	return (term);
}

/*====================================================================*
 *
 *   TREE * dcl:;line ();
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

TREE * odcl::line ()

{
	extern signed c;
	TREE * line = odcl::term ();
	TREE * term = line;
	while (c != EOF)
	{
		while (std::isspace (c))
		{
			c = odcl::grab ();
		}
		if (c == '/')
		{
			c = odcl::grab ();
			term->list = odcl::list ('/', odcl::term);
			continue;
		}
		if (std::isalnum (c))
		{
			term->next = odcl::term ();
			term = term->next;
			continue;
		}
		break;
	}
	return (line);
}

/*====================================================================*
 *
 *   void init ();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void odcl::init ()

{
	odcl::string = odcl::buffer;
	return;
}

/*====================================================================*
 *
 *   void display (TREE * node);
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void odcl::display (TREE * node)

{
	static unsigned level = 0;
	static unsigned count = 0;
	level++;
	while (node)
	{
		for (count = 1; count < level; count ++)
		{
			std::cout << odcl::indent;
		}
		std::cout << "[" << node->name << "]" << std::endl;
		odcl::display (node->list);
		node = node->next;
	}
	level--;
	return;
}

/*====================================================================*
 *
 *   void discard (TREE * node);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void odcl::discard (TREE * list)

{
	while (list)
	{
		TREE * item = list;
		list = list->next;
		odcl::discard (item->list);
		std::memset (item, 0, sizeof (* item));
		delete item;
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

int main (int argc, char const * argv [])

{
	extern signed c;
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
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	while (~ (c = odcl::grab (STDIN_FILENO)))
	{
		node = odcl::line ();
		if ((c != ';') && (c != EOF))
		{
			edl::error (1, 0, odcl::format, c, ';');
		}
		odcl::tree (node);
		odcl::free (node);
	}
	return (0);
}

#endif

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#endif



