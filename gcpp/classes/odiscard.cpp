/*====================================================================*
 *
 *   odiscard.cpp - implementation of the odiscard class.
 *
 *   consume and discard segments of well-formed source code;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oDISCARD_SOURCE
#define oDISCARD_SOURCE

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
#include "../classes/odiscard.hpp"

/*====================================================================*
 *   
 *   signed context (signed c, char const * charset) const;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

signed odiscard::context (signed c, char const * charset) const 

{
	while ((c) && !std::strchr (charset, c) && (c != EOF)) 
	{
		c = odiscard::context (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed context (signed c, signed o, signed e) const;
 *
 *   discard context terminated by an inverted pair occuring at the
 *   same nested level as character (c);  
 *
 *   examples: {*.  Motley Tools by Charles Maier
 * 
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed odiscard::context (signed c, signed o, signed e) const 

{
	c = odiscard::feed (c);
	c = odiscard::_context (c, o, e);
	c = odiscard::feed (c);
	return (c);
}

signed odiscard::_context (signed c, signed o, signed e) const 

{
	while ((c != e) && (c != EOF)) 
	{
		c = odiscard::_context (c, o);
		c = odiscard::feed (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed context (signed c, signed e) const;
 *
 *   discard context terminated character (e) occuring at the same
 *   nested level as character (c);
 *
 *   examples: (...) [...] {...}
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed odiscard::context (signed c, signed e) const 

{
	c = odiscard::feed (c);
	c = odiscard::_context (c, e);
	c = odiscard::feed (c);
	return (c);
}

signed odiscard::_context (signed c, signed e) const 

{
	while ((c != e) && (c != EOF)) 
	{
		c = odiscard::context (c);
	}
	return (c);
}

/*====================================================================*
 *   
 *   signed context (signed c) const;
 *
 *   discard current character (c) and return the next character at
 *   the same nested level as character (c); discard intervening
 *   comments, literals and nested substrings;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

signed odiscard::context (signed c) const 

{
	if (c == '/') 
	{
		c = odiscard::comment (c);
	}
	else if (oascii::isquote (c)) 
	{
		c = odiscard::literal (c);
	}
	else if (c == '#') 
	{
		c = odiscard::command (c, '\n');
	}
	else if (c == '(') 
	{
		c = odiscard::context (c, ')');
	}
	else if (c == '[') 
	{
		c = odiscard::context (c, ']');
	}
	else if (c == '{') 
	{
		c = odiscard::context (c, '}');
	}
	else
	{
		c = odiscard::feed (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed comment (signed c) const;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed odiscard::comment (signed c) const 

{
	c = std::cin.get ();
	if (c == '/') 
	{
		c = odiscard::content (c, '\n');
		return (c);
	}
	if (c == '*') 
	{
		c = odiscard::content (c, '*', '/');
		return (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed odiscard::content (signed c, signed o, signed e) const;
 *
 *   discard content terminated by an inverted pair;  
 *
 *   examples: {*.  Motley Tools by Charles Maier
 * 
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed odiscard::content (signed c, signed o, signed e) const 

{
	c = odiscard::feed (c);
	c = odiscard::_content (c, o, e);
	c = odiscard::feed (c);
	return (c);
}

signed odiscard::_content (signed c, signed o, signed e) const 

{
	while ((c != e) && (c != EOF)) 
	{
		c = odiscard::_content (c, o);
		c = odiscard::feed (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed odiscard::content (signed c, signed e) const;
 *   
 *   discard content; content can contain anything but nothing is
 *   special; comments, literals and escaped characters have no
 *   significance;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed odiscard::content (signed c, signed e) const 

{
	c = odiscard::feed (c);
	c = odiscard::_content (c, e);
	c = odiscard::feed (c);
	return (c);
}

signed odiscard::_content (signed c, signed e) const 

{
	while ((c != e) && (c != EOF)) 
	{
		c = odiscard::feed (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed odiscard::command (signed c) const;
 *   signed odiscard::command (signed c, signed e) const;
 *
 *   discard processor directives; directives can contain comments, 
 *   literals and escaped characters;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed odiscard::command (signed c) const 

{
	c = odiscard::feed (c);
	c = odiscard::_command (c, '\n');
	c = odiscard::feed (c);
	return (c);
}

signed odiscard::command (signed c, signed e) const 

{
	c = odiscard::feed (c);
	c = odiscard::_command (c, e);
	c = odiscard::feed (c);
	return (c);
}

signed odiscard::_command (signed c, signed e) const 

{
	while ((c != e) && (c != EOF)) 
	{
		if (oascii::isquote (c)) 
		{
			c = odiscard::literal (c);
			continue;
		}
		if (c == '/') 
		{
			c = odiscard::comment (c);
			continue;
		}
		c = odiscard::escaped (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed odiscard::literal (signed c) const;
 *   signed odiscard::literal (signed c, signed e) const;
 *
 *   discard literal strings; literals can contain anything except
 *   terminator (e) but escaped terminators are ignored;
 *
 *   examples: "..." '...' &...; #...\n 
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed odiscard::literal (signed c) const 

{
	c = odiscard::literal (c, c);
	return (c);
}

signed odiscard::literal (signed c, signed e) const 

{
	c = odiscard::feed (c);
	c = odiscard::_literal (c, e);
	c = odiscard::feed (c);
	return (c);
}

signed odiscard::_literal (signed c, signed e) const 

{
	while ((c != e) && (c != EOF)) 
	{
		c = odiscard::escaped (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed odiscard::escaped (signed c) const;
 *
 *   discard escaped characters; the escape character is backslash;
 *   call this function to detect an escape character then discard
 *   the escaped character, if appropriate;
 *
 *   examples: "\n" "\t" "\\"
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed odiscard::escaped (signed c) const 

{
	if (c == '\\') 
	{
		c = odiscard::feed (c);
	}
	c = odiscard::feed (c);
	return (c);
}

/*====================================================================*
 *
 *   signed find (signed c) const;
 *
 *   read and discard whitespace; start with current character (c);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed odiscard::find (signed c) const 

{
	while (oascii::isspace (c)) 
	{
		c = odiscard::feed (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed feed (signed c) const;
 *
 *   read and discard whitespace; start with current character (c);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed odiscard::feed (signed c) const 

{
	c = std::cin.get ();
	return (c);
}

/*====================================================================*
 *
 *   odiscard (void)
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

odiscard::odiscard (void) 

{
	return;
}

/*====================================================================*
 *
 *   ~odiscard (void)
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

odiscard::~odiscard (void) 

{
	return;
}

/*====================================================================*
 *   end implementation
 *--------------------------------------------------------------------*/

#endif

