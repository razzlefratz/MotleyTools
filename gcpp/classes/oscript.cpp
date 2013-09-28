/*====================================================================*
 *
 *   oscript.cpp - implementation of the oscript class.
 *
 *   the oscript class implements a range of test scanning primatives
 *   used to format C, C++, PHP, HTML, XML and other forms of source
 *   code by inspecting the punctuation and manipulating supprounding
 *   white space;
 *
 *   additions to this class MUST be independent of language keywords
 *   and constructs;
 *
 *   this class is used by programs ctidy, phptidy, csstidy, dnstidy,
 *   and cfm;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oSCRIPT_SOURCE
#define oSCRIPT_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdio>
#include <cstring>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oascii.hpp"
#include "../classes/oscript.hpp"
#include "../classes/oindent.hpp"
#include "../../gcc/tools/symbol.h"

/*====================================================================*
 *
 *   signed content (signed c, signed o, signed e) const;
 *
 *   write (c) then read and write characters up to pair (oe); write
 *   both (o) and (e) then return either the next character or EOF;
 *
 *   for example, content ('{', '*', '}') collects pascal comments;
 *
 *--------------------------------------------------------------------*/

signed oscript::content (signed c, signed o, signed e) const

{
	c = oscript::feed (c);
	c = oscript::_content (c, o, e);
	c = oscript::feed (c);
	return (c);
}

signed oscript::_content (signed c, signed o, signed e) const

{
	while ((c != e) && (c != EOF))
	{
		c = oscript::_content (c, o);
		c = oscript::feed (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed content (signed c, signed e) const;
 *
 *   write (c) then read and write characters until (e); write (e)
 *   then return the next character;
 *
 *   this method is used to scan text having distinct start and end
 *   characters but no special constructs within; some examples are
 *   shell sript comments and C++ comments;
 *
 *   for example content ('#', '\n') collects an entire shell script
 *   comment and return the first character on the next line;
 *
 *   this method preserves start and end characters and all internal
 *   spacing and escape sequences;
 *
 *--------------------------------------------------------------------*/

signed oscript::content (signed c, signed e) const

{
	c = oscript::feed (c);
	c = oscript::_content (c, e);
	c = oscript::feed (c);
	return (c);
}

/*====================================================================*
 *
 *   signed content (signed c, signed e) const;
 *
 *   inspect (c) the write and read characters until (e); return (e)
 *   or EOF to the caller;
 *
 *   this method unconditionally writes text up to, but excluding, a
 *   specific terminating character such as a newline or semicolon;
 *(
 *   it can be used to detect the inside character of a terminating
 *   inverted pair;
 *
 *--------------------------------------------------------------------*/

signed oscript::_content (signed c, signed e) const

{
	while ((c != e) && (c != EOF))
	{
		c = oscript::feed (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed context (signed c, char const * charset) const;
 *
 *--------------------------------------------------------------------*/

signed oscript::context (signed c, char const * charset) const

{
	while ((c) && (c != EOF) && ! std::strchr (charset, c))
	{
		c = oscript::context (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed context (signed c, signed o, signed e) const;
 *   signed _context (signed c, signed o, signed e) const;
 *
 *--------------------------------------------------------------------*/

signed oscript::context (signed c, signed o, signed e) const

{
	c = oscript::feed (c);
	c = oscript::find (c);
	c = oscript::_context (c, o, e);
	c = oscript::feed (c);
	return (c);
}

signed oscript::_context (signed c, signed o, signed e) const

{
	while ((c != e) && (c != EOF))
	{
		c = oscript::_context (c, o);
		c = oscript::feed (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed context (signed c, signed e) const;
 *
 *--------------------------------------------------------------------*/

signed oscript::context (signed c, signed e) const

{
	c = oscript::feed (c);
	c = oscript::find (c);
	c = oscript::_context (c, e);
	c = oscript::feed (c);
	return (c);
}

signed oscript::_context (signed c, signed e) const

{
	while ((c != e) && (c != EOF))
	{
		c = oscript::context (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed context (signed c) const;
 *
 *   read stdin and write stdout; write initiator (c) then read and
 *   write trailing characters upto and including any terminator in
 *   string;
 *
 *   ignore terminators in character or string literals or enclosed
 *   by nested "(...)", "[...]" or "{...}" groups;
 *
 *--------------------------------------------------------------------*/

signed oscript::context (signed c) const

{
	if (oascii::isquote (c))
	{
		c = oscript::literal (c);
	}
	else if (c == '/')
	{
		c = oscript::comment (c);
	}
	else if (c == '#')
	{
		c = oscript::command (c);
	}
	else if (c == '(')
	{
		c = oscript::context (c, ')');
	}
	else if (c == '[')
	{
		c = oscript::context (c, ']');
	}
	else if (c == '{')
	{
		c = oscript::context (c, '}');
	}
	else 
	{
		c = oscript::feed (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed oscript::command (signed c) const;
 *   signed oscript::command (signed c, signed e) const;
 *
 *   write (c) then read and write characters until (e); write (e)
 *   then return the next character;
 *
 *   ignore escaped terminators and terminators inside literals and
 *   comments;
 *
 *   this methods is suitable for C language style macro processor
 *   commands that contain literals and support continuation lines;
 *
 *--------------------------------------------------------------------*/

signed oscript::command (signed c) const

{
	c = oscript::command (c, '\n');
	return (c);
}

signed oscript::command (signed c, signed e) const

{
	c = oscript::feed (c);
	c = oscript::_command (c, e);
	c = oscript::feed (c);
	return (c);
}

signed oscript::_command (signed c, signed e) const

{
	while ((c != e) && (c != EOF))
	{
		if (oascii::isquote (c))
		{
			c = oscript::literal (c);
			continue;
		}
		if (c == '/')
		{
			c = oscript::comment (c);
			continue;
		}
		c = oscript::escaped (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed oscript::literal (signed c) const;
 *
 *   output (c) then read and write characters upto the next (c);
 *   output (c) and return the next character; ignore escaped
 *   instances of (e);
 *
 *--------------------------------------------------------------------*/

signed oscript::literal (signed c) const

{
	c = oscript::literal (c, c);
	return (c);
}

/*====================================================================*
 *
 *   signed oscript::literal (signed c, signed e) const;
 *
 *   read and write characters up to (e); output (e) and return the
 *   next character; ignore escaped instances of (e);
 *
 *--------------------------------------------------------------------*/

signed oscript::literal (signed c, signed e) const

{
	c = oscript::feed (c);
	c = oscript::_literal (c, e);
	c = oscript::feed (c);
	return (c);
}

/*====================================================================*
 *
 *   signed oscript::_literal (signed c, signed e) const;
 *
 *   read and write characters up to (e); return (e); ignore escaped
 *   instances of (e);
 *
 *--------------------------------------------------------------------*/

signed oscript::_literal (signed c, signed e) const

{
	while ((c != e) && (c != EOF))
	{
		c = oscript::escaped (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed comment (signed c) const;
 *
 *   process multi-line comments; pad left margin with asterisks;
 *   donot manipulate comment content;
 *
 *--------------------------------------------------------------------*/

signed oscript::comment (signed c) const

{
	c = oscript::feed (c);
	if (c == '/')
	{
		c = oscript::content (c, '\n');
		return (c);
	}
	if (c == '*')
	{
		while ((c != '/') && (c != EOF))
		{
			while ((c != '*') && (c != EOF))
			{
				std::cout.put (c);
				if (c == '\n')
				{
					std::cout.put (' ');
					do 
					{
						c = std::cin.get ();
					}
					while (oascii::isblank (c));
					if (c != '*')
					{
						std::cout.put ('*');
						std::cout.put (' ');
						std::cout.put (' ');
						std::cout.put (' ');
					}
					continue;
				}
				c = std::cin.get ();
			}
			c = oscript::feed (c);
		}
		c = oscript::feed (c);
		return (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed _comment (signed c) const ;
 *
 *
 *--------------------------------------------------------------------*/

signed oscript::_comment (signed c) const

{
	c = oscript::feed (c);
	if (c == '/')
	{
		c = oscript::content (c, '\n');
		return (c);
	}
	if (c == '*')
	{
		c = oscript::content (c, c, '/');
		return (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed oscript::moniker (signed c) const;
 *
 *   read and write alphanumeric characters and underscore; do not
 *   call istoken () here because colon and hyphen are treated as
 *   part of the name and that conflicts with labels, arithmetic
 *   operators and pointer operators;
 *
 *--------------------------------------------------------------------*/

signed oscript::moniker (signed c) const

{
	do 
	{
		c = oscript::feed (c);
	}
	while (oascii::isalnum (c) || (c == '_'));
	return (c);
}

/*====================================================================*
 *
 *   signed oscript::numeric (signed c) const;
 *
 *   read and write alphanumeric characters and underscore; do not
 *   call istoken () here because colon and hyphen are treated as
 *   part of the name and that conflicts with labels, arithmetic
 *   operators and pointer operators;
 *
 *--------------------------------------------------------------------*/

signed oscript::numeric (signed c) const

{
	do 
	{
		c = oscript::feed (c);
	}
	while (oascii::isalnum (c) || (c == '.'));
	return (c);
}

/*====================================================================*
 *
 *   signed oscript::escaped (signed c) const;
 *
 *   write (c) and read the next character; repeat once if (c) is
 *   the escape meta character;
 *
 *   this method is used to ignore special characters such as quotes
 *   and newlines within literals;
 *
 *--------------------------------------------------------------------*/

signed oscript::escaped (signed c) const

{
	if (c == '\\')
	{
		c = oscript::feed (c);
	}
	c = oscript::feed (c);
	return (c);
}

/*====================================================================*
 *
 *   signed feed (signed c) const;
 *
 *   inspect (c); write (c) then read and return the next character
 *   if (c) is not NUL or EOF;
 *
 *--------------------------------------------------------------------*/

signed oscript::feed (signed c) const

{
	if ((c != NUL) && (c != EOF))
	{
		std::cout.put (c);
	}
	c = std::cin.get ();
	return (c);
}

/*====================================================================*
 *
 *   signed find (signed c) const;
 *
 *   inspect (c); read and discard white space characters; return
 *   the next non-space input character;
 *
 *--------------------------------------------------------------------*/

signed oscript::find (signed c) const

{
	while (oascii::isspace (c))
	{
		c = oscript::feed (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   oscript ();
 *
 *--------------------------------------------------------------------*/

oscript::oscript ()

{
	return;
}

/*====================================================================*
 *
 *   ~oscript ();
 *
 *--------------------------------------------------------------------*/

oscript::~ oscript ()

{
	return;
}

/*====================================================================*
 *   end implementation
 *--------------------------------------------------------------------*/

#endif



