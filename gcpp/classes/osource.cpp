/*====================================================================*
 *
 *   osource.cpp - implementation of the osource class.
 *
 *   the osource class implements a range of test scanning primatives
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

#ifndef oSOURCE_SOURCE
#define oSOURCE_SOURCE

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

signed osource::content (signed c, signed e) const 

{ 
	c = osource::feed (c); 
	c = osource::_content (c, e); 
	c = osource::feed (c); 
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
 *   signed context (signed c, char const * charset) const;
 *   
 *--------------------------------------------------------------------*/

signed osource::context (signed c, char const * charset) const 

{ 
	while ((c) && (c != EOF) && !std::strchr (charset, c)) 
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
	if (oascii::isquote (c)) 
	{ 
		c = osource::literal (c); 
	} 
	else if (c == '/') 
	{ 
		c = osource::comment (c); 
	} 
	else if (c == '#') 
	{ 
		c = osource::command (c); 
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
 *   signed osource::command (signed c) const;
 *   signed osource::command (signed c, signed e) const;
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

signed osource::command (signed c) const 

{ 
	c = osource::command (c, '\n'); 
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
		if (c == '\\') 
		{ 
			c = osource::feed (c); 
		} 
		c = osource::feed (c); 
	} 
	return (c); 
} 

/*====================================================================*
 *
 *   signed osource::literal (signed c) const;
 *   
 *   output (c) then read and write characters upto the next (c); 
 *   output (c) and return the next character; ignore escaped 
 *   instances of (e);
 *
 *--------------------------------------------------------------------*/

signed osource::literal (signed c) const 

{ 
	c = osource::literal (c, c); 
	return (c); 
} 

/*====================================================================*
 *
 *   signed osource::literal (signed c, signed e) const;
 *   
 *   read and write characters up to (e); output (e) and return the
 *   next character; ignore escaped instances of (e);
 *
 *--------------------------------------------------------------------*/

signed osource::literal (signed c, signed e) const 

{ 
	c = osource::feed (c); 
	c = osource::_literal (c, e); 
	c = osource::feed (c); 
	return (c); 
} 

/*====================================================================*
 *
 *   signed osource::_literal (signed c, signed e) const;
 *   
 *   read and write characters up to (e); return (e); ignore escaped
 *   instances of (e);
 *
 *--------------------------------------------------------------------*/

signed osource::_literal (signed c, signed e) const 

{ 
	while ((c != e) && (c != EOF)) 
	{ 
		if (c == '\\') 
		{ 
			c = osource::feed (c); 
		} 
		c = osource::feed (c); 
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

/*====================================================================*
 *
 *   signed _comment (signed c) const ;
 *   
 *
 *--------------------------------------------------------------------*/

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
		c = osource::content (c, c, '/'); 
		return (c); 
	} 
	return (c); 
} 

/*====================================================================*
 *
 *   signed osource::moniker (signed c) const;
 *
 *   read and write alphanumeric characters and underscore; do not
 *   call istoken () here because colon and hyphen are treated as
 *   part of the name and that conflicts with labels, arithmetic
 *   operators and pointer operators;
 *
 *--------------------------------------------------------------------*/

signed osource::moniker (signed c) const 

{ 
	do 
	{ 
		c = osource::feed (c); 
	} 
	while (oascii::isalnum (c) || (c == '_')); 
	return (c); 
} 

/*====================================================================*
 *
 *   signed osource::numeric (signed c) const;
 *
 *   read and write alphanumeric characters and underscore; do not
 *   call istoken () here because colon and hyphen are treated as
 *   part of the name and that conflicts with labels, arithmetic
 *   operators and pointer operators;
 *
 *--------------------------------------------------------------------*/

signed osource::numeric (signed c) const 

{ 
	do 
	{ 
		c = osource::feed (c); 
	} 
	while (oascii::isalnum (c) || (c == '.')); 
	return (c); 
} 

/*====================================================================*
 *
 *   signed terminate (signed c) const;
 *   
 *
 *--------------------------------------------------------------------*/

signed osource::terminate (signed c) const 

{ 
	if (oascii::isalnum (c) || (c == '_')) 
	{ 
		std::cout.put (' '); 
	} 
	else if (oascii::isquote (c)) 
	{ 
		std::cout.put (' '); 
	} 
	else if (oascii::isbegin (c)) 
	{ 
		std::cout.put (' '); 
	} 
	else if (oascii::isequal (c)) 
	{ 
		std::cout.put (' '); 
	} 
	else if (oascii::islogic (c)) 
	{ 
		std::cout.put (' '); 
	} 
	else if (oascii::isarith (c))
	{ 
		if (c == '+') 
		{	 
			if (std::cin.peek () == c) 
			{	 
				return (c); 
			} 
		} 
		else if (c == '-') 
		{ 
			if (std::cin.peek () == '-') 
			{ 
				return (c); 
			} 
			if (std::cin.peek () == '>') 
			{ 
				return (c); 
			} 
		}
		std::cout.put (' '); 
	} 
	return (c); 
} 

/*====================================================================*
 *
 *   osource::operate (signed c) const;
 *
 *
 *
 *--------------------------------------------------------------------*/

signed osource::operate (signed c) const 

{ 
	if (oascii::isspace (c)) 
	{ 
		c = osource::find (c); 
		if (oascii::isclose (c)) 
		{ 
			return (c); 
		} 
		if (oascii::iscomma (c)) 
		{ 
			return (c); 
		} 
		if (c == '.') 
		{ 
			return (c); 
		} 
		std::cout.put (' '); 
	} 
	else if (oascii::isalpha (c) || (c == '_')) 
	{ 
		c = osource::moniker (c);
		c = osource::terminate (c); 
	} 
	else if (oascii::isdigit (c)) 
	{ 
		c = osource::numeric (c);
		c = osource::terminate (c); 
	} 
	else if (oascii::isquote (c)) 
	{ 
		c = osource::literal (c); 
		c = osource::terminate (c); 
	} 
	else if (c == '#') 
	{ 
		c = osource::command (c); 
	} 
	else if (c == '\\') 
	{ 
		c = osource::feed (c); 
		c = osource::feed (c); 
	} 
	else if ((c == '.') || (c == '!')) 
	{ 
		c = osource::feed (c); 
		c = osource::find (c); 
	} 
	else if ((c == ',') || (c == ';') || (c == '?')) 
	{ 
		c = osource::feed (c); 
		c = osource::find (c); 
		std::cout.put (' '); 
	} 
	else if ((c == '=') || (c == '^') || (c == '%') || (c == '~')) 
	{ 
		c = osource::feed (c); 
		if (c == '=') 
		{ 
			c = osource::feed (c); 
		} 
		c = osource::find (c); 
		std::cout.put (' '); 
	} 
	else if ((c == '&') || (c == '|')) 
	{ 
		signed o = osource::feed (c); 
		if ((o == c) || (o == '=')) 
		{ 
			o = osource::feed (o); 
		} 
		c = osource::find (o); 
		std::cout.put (' '); 
	} 
	else if ((c == '<') || (c == '>')) 
	{ 
		signed o = osource::feed (c); 
		if (o == c) 
		{ 
			o = osource::feed (o); 
		} 
		if (o == '=') 
		{ 
			o = osource::feed (o); 
		} 
		c = osource::find (o); 
		std::cout.put (' '); 
	} 
	else if (c == ':') 
	{ 
		c = osource::feed (c); 
		if (c == ':') 
		{ 
			c = osource::feed (c); 
			c = osource::find (c); 
			return (c);
		} 
		c = osource::find (c); 
		std::cout.put (' '); 
	} 
	else if (c == '+') 
	{ 
		c = osource::feed (c); 
		if (c == '+') 
		{ 
			c = osource::feed (c); 
			c = osource::find (c); 
			if (oascii::isclose (c)) 
			{ 
				return (c); 
			} 
			if (oascii::iscomma (c)) 
			{ 
				return (c); 
			} 
		} 
		else if (c == '=') 
		{ 
			c = osource::feed (c); 
			c = osource::find (c); 
		} 
		std::cout.put (' '); 
	} 
	else if (c == '-') 
	{ 
		c = osource::feed (c); 
		if (c == '-') 
		{ 
			c = osource::feed (c); 
			c = osource::find (c); 
			if (oascii::isclose (c)) 
			{ 
				return (c); 
			} 
			if (oascii::iscomma (c)) 
			{ 
				return (c); 
			} 
		} 
		else if (c == '=') 
		{ 
			c = osource::feed (c); 
			c = osource::find (c); 
		} 
		else if (c == '>') 
		{ 
			c = osource::feed (c); 
			c = osource::find (c); 
			return (c);
		} 
		else 
		{ 
			c = osource::find (c); 
		} 
		std::cout.put (' '); 
	} 
	else if (c == '*') 
	{ 
		c = osource::feed (c); 
		if ((c == '*') || (c == '=')) 
		{ 
			c = osource::feed (c); 
		} 
		c = osource::find (c); 
		if (oascii::isclose (c)) 
		{ 
			return (c); 
		} 
		if (oascii::iscomma (c)) 
		{ 
			return (c); 
		} 
		std::cout.put (' '); 
	} 
	else if (c == '/') 
	{ 
		c = osource::feed (c); 
		if (c == '=') 
		{ 
			c = osource::feed (c); 
			c = osource::find (c); 
			std::cout.put (' '); 
		} 
		else if (c == '/') 
		{ 
			c = osource::content (c, '\n'); 
		} 
		else if (c == '*') 
		{ 
			c = osource::content (c, c, '/'); 
		} 
		else 
		{
			c = osource::find (c); 
			std::cout.put (' '); 
		}
	} 
	else 
	{ 
		c = osource::feed (c); 
	} 
	return (c); 
} 

/*====================================================================*
 *
 *   signed osource::escaped (signed c) const;
 * 
 *   write (c) and read the next character; repeat once if (c) is
 *   the escape meta character;
 *   
 *   this method is used to ignore special characters such as quotes
 *   and newlines within literals; 
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
 *   signed feed (signed c) const;
 *
 *   inspect (c); write (c) then read and return the next character
 *   if (c) is not NUL or EOF;
 *   
 *--------------------------------------------------------------------*/

signed osource::feed (signed c) const 

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

signed osource::find (signed c) const 

{ 
	while (oascii::isspace (c)) 
	{ 
		c = std::cin.get (); 
	} 
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

osource::~ osource () 

{ 
	return; 
} 

/*====================================================================*
 *   end implementation
 *--------------------------------------------------------------------*/

#endif


