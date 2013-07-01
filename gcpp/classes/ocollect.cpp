/*====================================================================*
 *
 *   ocollect.cpp - implementation of the ocollect class.
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
#include "../classes/ocollect.hpp"
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

signed ocollect::context (signed c, char const * charset) const 

{
	while ((c) && !std::strchr (charset, c) && (c != EOF)) 
	{
		c = ocollect::context (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed context (signed c, signed o, signed e) const;
 *   signed _context (signed c, signed o, signed e) const;
 *
 *--------------------------------------------------------------------*/

signed ocollect::context (signed c, signed o, signed e) const 

{
	c = ocollect::feed (c);
	c = ocollect::_context (c, o, e);
	c = ocollect::feed (c);
	return (c);
}

signed ocollect::_context (signed c, signed o, signed e) const 

{
	while ((c != e) && (c != EOF)) 
	{
		c = ocollect::_context (c, o);
		c = ocollect::feed (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed context (signed c, signed e) const;
 *   signed _context (signed c, signed e) const;
 *
 *--------------------------------------------------------------------*/

signed ocollect::context (signed c, signed e) const 

{
	c = ocollect::feed (c);
	c = ocollect::_context (c, e);
	c = ocollect::feed (c);
	return (c);
}

signed ocollect::_context (signed c, signed e) const 

{
	while ((c != e) && (c != EOF)) 
	{
		c = ocollect::context (c);
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

signed ocollect::context (signed c) const 

{
	if (c == '/') 
	{
		c = ocollect::comment (c);
	}
	else if (oascii::isquote (c)) 
	{
		c = ocollect::literal (c);
	}
	else if (c == '#') 
	{
		c = ocollect::command (c, '\n');
	}
	else if (c == '(') 
	{
		c = ocollect::context (c, ')');
	}
	else if (c == '[') 
	{
		c = ocollect::context (c, ']');
	}
	else if (c == '{') 
	{
		c = ocollect::context (c, '}');
	}
	else 
	{
		c = ocollect::feed (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed comment (signed c) const;
 *
 *--------------------------------------------------------------------*/

signed ocollect::comment (signed c) const 

{
	c = ocollect::feed (c);
	if (c == '/') 
	{
		c = ocollect::content (c, '\n');
		return (c);
	}
	if (c == '*') 
	{
		c = ocollect::content (c, '*', '/');
		return (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed ocollect::content (signed c, signed o, signed e) const;
 *   signed ocollect::_content (signed c, signed o, signed e) const;
 *
 *   write (c) then read and write characters up to pair (oe); write
 *   both (o) and (e) then return either the next character or EOF;
 *
 *   for example, content ('{', '*', '}') collects pascal comments;
 *
 *--------------------------------------------------------------------*/

signed ocollect::content (signed c, signed o, signed e) const 

{
	c = ocollect::feed (c);
	c = ocollect::_content (c, o, e);
	c = ocollect::feed (c);
	return (c);
}

signed ocollect::_content (signed c, signed o, signed e) const 

{
	while ((c != e) && (c != EOF)) 
	{
		c = ocollect::_content (c, o);
		c = ocollect::feed (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed ocollect::content (signed c, signed e) const;
 *   signed ocollect::_content (signed c, signed e) const;
 *
 *   write (c) then read and write characters until (e); write (e) 
 *   then return the next character;
 *
 *   this method is suitabl for FORTRAN style comments that have no
 *   special constructs from start of comment to end of line;
 *
 *--------------------------------------------------------------------*/

signed ocollect::content (signed c, signed e) const 

{
	c = ocollect::feed (c);
	c = ocollect::_content (c, e);
	c = ocollect::feed (c);
	return (c);
}

signed ocollect::_content (signed c, signed e) const 

{
	while ((c != e) && (c != EOF)) 
	{
		c = ocollect::feed (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed ocollect::command (signed c) const;
 *   signed ocollect::command (signed c, signed e) const;
 *   signed ocollect::_command (signed c, signed e) const;
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

signed ocollect::command (signed c) const 

{
	c = ocollect::feed (c);
	c = ocollect::_command (c, '\n');
	c = ocollect::feed (c);
	return (c);
}

signed ocollect::command (signed c, signed e) const 

{
	c = ocollect::feed (c);
	c = ocollect::_command (c, e);
	c = ocollect::feed (c);
	return (c);
}

signed ocollect::_command (signed c, signed e) const 

{
	while ((c != e) && (c != EOF)) 
	{
		if (oascii::isquote (c)) 
		{
			c = ocollect::literal (c);
			continue;
		}
		if (c == '/') 
		{
			c = ocollect::comment (c);
			continue;
		}
		c = ocollect::escaped (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed ocollect::literal (signed c) const;
 *   signed ocollect::literal (signed c, signed e) const;
 *   
 *   read and write characters up to (e); output (e) then return the
 *   next character or EOF; ignore escaped instances of (e);
 *
 *--------------------------------------------------------------------*/

signed ocollect::literal (signed c) const 

{
	c = ocollect::literal (c, c);
	return (c);
}

signed ocollect::literal (signed c, signed e) const 

{
	c = ocollect::feed (c);
	c = ocollect::_literal (c, e);
	c = ocollect::feed (c);
	return (c);
}

signed ocollect::_literal (signed c, signed e) const 

{
	while ((c != e) && (c != EOF)) 
	{
		c = ocollect::escaped (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed ocollect::escaped (signed c) const;
 *   
 *--------------------------------------------------------------------*/

signed ocollect::escaped (signed c) const 

{
	if (c == '\\') 
	{
		c = ocollect::feed (c);
	}
	c = ocollect::feed (c);
	return (c);
}

/*====================================================================*
 *   
 *   signed find (signed c) const;
 *
 *   return the next non-space input character;
 *   
 *--------------------------------------------------------------------*/

signed ocollect::find (signed c) const 

{
	while (oascii::isspace (c)) 
	{
		c = ocollect::feed (c);
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

signed ocollect::feed (signed c) const 

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
 *   ocollect ();
 *
 *--------------------------------------------------------------------*/

ocollect::ocollect () 

{
	return;
}

/*====================================================================*
 *
 *   ~ocollect ();
 *
 *--------------------------------------------------------------------*/

ocollect::~ocollect () 

{
	return;
}

/*====================================================================*
 *   end implementation
 *--------------------------------------------------------------------*/

#endif

