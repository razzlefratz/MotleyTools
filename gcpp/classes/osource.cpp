/*====================================================================*
 *
 *   osource.cpp - implementation of the osource class.
 *
 *   this is a generic source code formatter for C-style languages 
 *   such as C, C++, PHP, CSS and DNS; 
 *
 *   it is used by programs ctidy, phptidy, csstidy, dnstidy;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCOLLECT_SOURCE
#define oCOLLECT_SOURCE

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
#include "../classes/osource.hpp"
#include "../../gcc/tools/symbol.h"

/*====================================================================*
 *   
 *   signed context (signed c, char const * charset) const;
 *   
 *   read stdin and write stdout; write initiator (c) then read and 
 *   write trailing characters upto and including any terminator in
 *   string; 
 *
 *   ignore terminators in character or string literals or enclosed
 *   by nested "(...)", "[...]" or "{...}" groups;
 *   
 *   remove white spaces preceding ',' or ';' and insert one space
 *   after each ',' or ';'; replace other white space strings with
 *   one space;
 *
 *--------------------------------------------------------------------*/

signed osource::context (signed c, char const * charset) const 

{
	while ((c) && !std::strchr (charset, c) && (c != EOF)) 
	{
		c = osource::context (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed context (signed c, signed o, signed e) const;
 *   signed _context (signed c, signed o, signed e) const;
 *
 *--------------------------------------------------------------------*/

signed osource::context (signed c, signed o, signed e) const 

{
	c = osource::feed (c);
	c = osource::find (c);
	c = osource::_context (c, o, e);
	c = osource::feed (c);
	return (c);
}

signed osource::_context (signed c, signed o, signed e) const 

{
	while ((c != e) && (c != EOF)) 
	{
		c = osource::_context (c, o);
		c = osource::feed (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed context (signed c, signed e) const;
 *
 *--------------------------------------------------------------------*/

signed osource::context (signed c, signed e) const 

{
	c = osource::feed (c);
	c = osource::find (c);
	c = osource::_context (c, e);
	c = osource::feed (c);
	return (c);
}

signed osource::_context (signed c, signed e) const 

{
	while ((c != e) && (c != EOF)) 
	{
		c = osource::context (c);
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

signed osource::context (signed c) const 

{
	if (c == '/') 
	{
		c = osource::comment (c);
	}
	else if (oascii::isquote (c)) 
	{
		c = osource::literal (c);
	}
	else if (c == '#') 
	{
		c = osource::command (c, '\n');
	}
	else if (c == '(') 
	{
		c = osource::context (c, ')');
	}
	else if (c == '[') 
	{
		c = osource::context (c, ']');
	}
	else if (c == '{') 
	{
		c = osource::context (c, '}');
	}
	else 
	{
		c = osource::feed (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed comment (signed c) const;
 *
 *   process multi-line comments; pad left margin with asterisks;
 *
 *--------------------------------------------------------------------*/

signed osource::comment (signed c) const 

{
	c = osource::feed (c);
	if (c == '/') 
	{
		c = osource::content (c, '\n');
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
			c = osource::feed (c);
		}
		c = osource::feed (c);
		return (c);
	}
	return (c);
}

signed osource::_comment (signed c) const 

{
	c = osource::feed (c);
	if (c == '/') 
	{
		c = osource::content (c, '\n');
		return (c);
	}
	if (c == '*') 
	{
		c = osource::content (c, '*', '/');
		return (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed osource::content (signed c, signed o, signed e) const;
 *
 *   write (c) then read and write characters up to pair (oe); write
 *   both (o) and (e) then return either the next character or EOF;
 *
 *   for example, content ('{', '*', '}') collects pascal comments;
 *
 *--------------------------------------------------------------------*/

signed osource::content (signed c, signed o, signed e) const 

{
	c = osource::feed (c);
	c = osource::_content (c, o, e);
	c = osource::feed (c);
	return (c);
}

signed osource::_content (signed c, signed o, signed e) const 

{
	while ((c != e) && (c != EOF)) 
	{
		c = osource::_content (c, o);
		c = osource::feed (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed osource::content (signed c, signed e) const;
 *
 *   write (c) then read and write characters until (e); write (e) 
 *   then return the next character;
 *
 *   this method is suitabl for FORTRAN style comments that have no
 *   special constructs from start of comment to end of line;
 *
 *--------------------------------------------------------------------*/

signed osource::content (signed c, signed e) const 

{
	c = osource::feed (c);
	c = osource::_content (c, e);
	c = osource::feed (c);
	return (c);
}

signed osource::_content (signed c, signed e) const 

{
	while ((c != e) && (c != EOF)) 
	{
		c = osource::feed (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed osource::command (signed c) const;
 *   signed osource::command (signed c, signed e) const;
 *
 *   read stdin and write stdout; write initiator c then read and
 *   write characters until terminator e; 
 *
 *   ignore escaped terminators and terminators inside literals and 
 *   comments; 
 *
 *   this methods is suitable for C language style macro processor 
 *   commands that contain literals and support continuation lines;
 *
 *--------------------------------------------------------------------*/

signed osource::command (signed c) const 

{
	c = osource::feed (c);
	c = osource::_command (c, '\n');
	c = osource::feed (c);
	return (c);
}

signed osource::command (signed c, signed e) const 

{
	c = osource::feed (c);
	c = osource::_command (c, e);
	c = osource::feed (c);
	return (c);
}

signed osource::_command (signed c, signed e) const 

{
	while ((c != e) && (c != EOF)) 
	{
		if (oascii::isquote (c)) 
		{
			c = osource::literal (c);
			continue;
		}
		if (c == '/') 
		{
			c = osource::comment (c);
			continue;
		}
		c = osource::escaped (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed osource::literal (signed c) const;
 *   signed osource::literal (signed c, signed e) const;
 *   
 *   read and write characters up to (e); output (e) then return the
 *   next character or EOF; ignore escaped instances of (e);
 *
 *--------------------------------------------------------------------*/

signed osource::literal (signed c) const 

{
	c = osource::literal (c, c);
	return (c);
}

signed osource::literal (signed c, signed e) const 

{
	c = osource::feed (c);
	c = osource::_literal (c, e);
	c = osource::feed (c);
	return (c);
}

signed osource::_literal (signed c, signed e) const 

{
	while ((c != e) && (c != EOF)) 
	{
		c = osource::escaped (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed osource::moniker (signed c) const;
 *
 *--------------------------------------------------------------------*/

signed osource::moniker (signed c) const 

{
	do 
	{
		c = osource::feed (c);
	}
	while (oascii::isalnum (c) || (c == '_') || (c == '.'));
	return (c);
}

/*====================================================================*
 *
 *   signed osource::escaped (signed c) const;
 *   
 *--------------------------------------------------------------------*/

signed osource::escaped (signed c) const 

{
	if (c == '\\') 
	{
		c = osource::feed (c);
	}
	c = osource::feed (c);
	return (c);
}

/*====================================================================*
 *   
 *   signed find (signed c) const;
 *
 *   return the next non-space input character;
 *   
 *--------------------------------------------------------------------*/

signed osource::find (signed c) const 

{
	while (oascii::isspace (c)) 
	{
		c = osource::feed (c);
	}
	return (c);
}

/*====================================================================*
 *   
 *   signed feed (signed c) const;
 *
 *   write (c) and return the next input character;
 *   
 *--------------------------------------------------------------------*/

signed osource::feed (signed c) const 

{
	if ((c) && (c != EOF)) 
	{
		std::cout.put (c);
	}
	c = std::cin.get ();
	return (c);
}

/*====================================================================*
 *
 *   osource ();
 *
 *--------------------------------------------------------------------*/

osource::osource () 

{
	return;
}

/*====================================================================*
 *
 *   ~osource ();
 *
 *--------------------------------------------------------------------*/

osource::~osource () 

{
	return;
}

/*====================================================================*
 *   end implementation
 *--------------------------------------------------------------------*/

#endif

