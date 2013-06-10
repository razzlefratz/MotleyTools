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
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
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
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ocollect::context (signed c, signed o, signed e) const 

{
	c = ocollect::keep (c);
	c = ocollect::inner_context (c, o, e);
	c = ocollect::keep (c);
	return (c);
}

signed ocollect::inner_context (signed c, signed o, signed e) const 

{
	while ((c != e) && (c != EOF)) 
	{
		c = ocollect::inner_context (c, o);
		c = ocollect::keep (c);
	}
	return (c);
}


/*====================================================================*
 *
 *   signed context (signed c, signed e);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ocollect::context (signed c, signed e) const 

{
	c = ocollect::keep (c);
	c = ocollect::inner_context (c, e);
	c = ocollect::keep (c);
	return (c);
}

signed ocollect::inner_context (signed c, signed e) const 

{
	while ((c != e) && (c != EOF)) 
	{
		c = ocollect::context (c);
	}
	return (c);
}


/*====================================================================*
 *   
 *   signed context (signed c);
 *   
 *   read stdin and write stdout; write initiator (c) then read and 
 *   write trailing characters upto and including any terminator in
 *   string; 
 *
 *   ignore terminators in character or string literals or enclosed
 *   by nested "(...)", "[...]" or "{...}" groups;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
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
		c = ocollect::keep (c);
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

signed ocollect::comment (signed c) const 

{
	c = ocollect::keep (c);
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
 *   signed ocollect::content (signed c, signed o, signed e);
 *
 *   write (c) then read and write characters up to pair (oe); write
 *   both (o) and (e) then return either the next character or EOF;
 *
 *   for example, content ('{', '*', '}') collects pascal comments;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ocollect::content (signed c, signed o, signed e) const 

{
	c = ocollect::keep (c);
	c = ocollect::inner_content (c, o, e);
	c = ocollect::keep (c);
	return (c);
}

signed ocollect::inner_content (signed c, signed o, signed e) const 

{
	while ((c != e) && (c != EOF)) 
	{
		c = ocollect::inner_content (c, o);
		c = ocollect::keep (c);
	}
	return (c);
}


/*====================================================================*
 *
 *   signed ocollect::content (signed c, signed e);
 *
 *   write (c) then read and write characters until (e); write (e) 
 *   then return the next character;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ocollect::content (signed c, signed e) const 

{
	c = ocollect::keep (c);
	c = ocollect::inner_content (c, e);
	c = ocollect::keep (c);
	return (c);
}

signed ocollect::inner_content (signed c, signed e) const 

{
	while ((c != e) && (c != EOF)) 
	{
		c = ocollect::keep (c);
	}
	return (c);
}


/*====================================================================*
 *
 *   signed ocollect::command (signed c) const;
 *   signed ocollect::command (signed c, signed e) const;
 *
 *   read stdin and write stdout; write initiator c then read and
 *   write characters until terminator e; 
 *
 *   ignore escaped terminators and terminators inside literals and 
 *   comments; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ocollect::command (signed c) const 

{
	c = ocollect::keep (c);
	c = ocollect::inner_command (c, '\n');
	c = ocollect::keep (c);
	return (c);
}

signed ocollect::command (signed c, signed e) const 

{
	c = ocollect::keep (c);
	c = ocollect::inner_command (c, e);
	c = ocollect::keep (c);
	return (c);
}

signed ocollect::inner_command (signed c, signed e) const 

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
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ocollect::literal (signed c) const 

{
	c = ocollect::literal (c, c);
	return (c);
}

signed ocollect::literal (signed c, signed e) const 

{
	c = ocollect::keep (c);
	c = ocollect::inner_literal (c, e);
	c = ocollect::keep (c);
	return (c);
}

signed ocollect::inner_literal (signed c, signed e) const 

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
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ocollect::escaped (signed c) const 

{
	if (c == '\\') 
	{
		c = ocollect::keep (c);
	}
	c = ocollect::keep (c);
	return (c);
}

/*====================================================================*
 *   
 *   signed find (signed c) const;
 *
 *   return the next non-space input character;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ocollect::find (signed c) const 

{
	while (oascii::isspace (c)) 
	{
		c = ocollect::keep (c);
	}
	return (c);
}


/*====================================================================*
 *
 *   signed ocollect::join (signed c) const;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ocollect::join (signed c) const 

{
	while (c == '\\')
	{
		signed o = std::cin.get ();
		if ((o != '\r') && (o != '\n'))
		{
			std::cout.put (c);
			std::cout.put (o);
		}
		c = std::cin.get ();
	} 
	return (c);
}



/*====================================================================*
 *   
 *   signed keep (signed c) const;
 *
 *   write (c) and return the next input character;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ocollect::keep (signed c) const 

{
	if (c != EOF) 
	{
		std::cout.put (c);
		c = std::cin.get ();
	}
	return (c);
}


/*====================================================================*
 *
 *   ocollect ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
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
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
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

