/*====================================================================*
 *
 *   oprogram.cpp - implementation of the oprogram class.
 *
 *   the oprogram class is a generic source code formatter for C-style
 *   languages including C, C++, PHP, java, CSS and DNS; as one example,
 *   this file was probably formatted by oprogram;
 *
 *   it is used by contexts ctidy, phptidy, csstidy, dnstidy;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oPROGRAM_SOURCE
#define oPROGRAM_SOURCE

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
#include "../classes/oprogram.hpp"

/*====================================================================*
 *   
 *   signed context (signed c, char const *charset) const;
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
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

signed oprogram::context (signed c, char const * charset) const 

{
	while ((c) && !std::strchr (charset, c) && (c != EOF)) 
	{
		c = oprogram::context (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed context (signed c, signed o, signed e) const;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed oprogram::context (signed c, signed o, signed e) const 

{
	c = oprogram::keep (c);
	c = oprogram::find (c);
	c = oprogram::inner_context (c, o, e);
	c = oprogram::keep (c);
	return (c);
}

signed oprogram::inner_context (signed c, signed o, signed e) const 

{
	while ((c != e) && (c != EOF)) 
	{
		c = oprogram::inner_context (c, o);
		c = oprogram::keep (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed context (signed c, signed e) const;
 *   
 *   write (c) then perform context-dependent formatting upto and 
 *   including (e) or EOF; return the next character or EOF as the
 *   function value;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed oprogram::context (signed c, signed e) const 

{
	c = oprogram::keep (c);
	c = oprogram::find (c);
	c = oprogram::inner_context (c, e);
	c = oprogram::keep (c);
	return (c);
}

signed oprogram::inner_context (signed c, signed e) const 

{
	while ((c != e) && (c != EOF)) 
	{
		c = oprogram::context (c);
	}
	return (c);
}

/*====================================================================*
 *   
 *   signed context (signed c) const;
 *
 *   write (c) then read (and possibley write) successive characters;
 *
 *   remove white space that precedes certain delimiters and output
 *   one space after others; output monikers, comments and literals
 *   directly;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

signed oprogram::context (signed c) const 

{
	if (oascii::isspace (c)) 
	{
		c = oprogram::find (c);
		if ((c == ',') || (c == ';') || (c == ':') || (c == '?')) 
		{
			return (c);
		}
		if ((c == ')') || (c == ']') || (c == '}')) 
		{
			return (c);
		}
		std::cout.put (' ');
	}
	else if ((c == ',') || (c == ';')) 
	{
		c = oprogram::keep (c);
		c = oprogram::find (c);
		std::cout.put (' ');
	}
	else if (oascii::isalpha (c) || (c == '_')) 
	{
		c = oprogram::moniker (c);
		if ((c == '(') || (c == '[') || (c == '{')) 
		{
			std::cout.put (' ');
		}
	}
	else if (oascii::isquote (c)) 
	{
		c = oprogram::literal (c);
	}
	else if (c == '/') 
	{
		c = oprogram::comment (c);
	}
	else if (c == '{') 
	{
		c = oprogram::context (c, '}');
	}
	else if (c == '[') 
	{
		c = oprogram::context (c, ']');
	}
	else if (c == '(') 
	{
		c = oprogram::context (c, ')');
	}
	else 
	{
		c = oprogram::keep (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed comment (signed c) const;
 *
 *   process multi-line comments; pad left margin with asterisks;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed oprogram::comment (signed c) const 

{
	c = oprogram::keep (c);
	if (c == '/') 
	{
		c = oprogram::content (c, '\n');
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
			c = oprogram::keep (c);
		}
		c = oprogram::keep (c);
		return (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed oprogram::moniker (signed c) const;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed oprogram::moniker (signed c) const 

{
	do 
	{
		c = oprogram::keep (c);
	}
	while (oascii::isalnum (c) || (c == '_') || (c == '.'));
	return (c);
}

/*====================================================================*
 *
 *   signed oprogram::requote (signed c, signed o, signed e) const;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed oprogram::requote (signed c, signed o, signed e) const 

{
	c = oprogram::keep (o);
	while ((c != e) && (c != EOF)) 
	{
		c = oprogram::escaped ((c == o)? e: c);
	}
	c = oprogram::keep (o);
	return (c);
}

/*====================================================================*
 *
 *   signed oprogram::find (signed c) const;
 *
 *   read and discard whitespace; return next character;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed oprogram::find (signed c) const 

{
	while (oascii::isspace (c)) 
	{
		c = std::cin.get ();
	}
	return (c);
}

/*====================================================================*
 *
 *   oprogram ()
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oprogram::oprogram () 

{
	return;
}

/*====================================================================*
 *
 *   ~oprogram ()
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oprogram::~oprogram () 

{
	return;
}

/*====================================================================*
 *   end implementation
 *--------------------------------------------------------------------*/

#endif

