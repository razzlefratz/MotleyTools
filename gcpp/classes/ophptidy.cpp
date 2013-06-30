/*====================================================================*
 *
 *   ophptidy.cpp - definition of ophptidy class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oPHPTIDY_SOURCE
#define oPHPTIDY_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cerrno>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oascii.hpp"
#include "../classes/ophptidy.hpp"

/*====================================================================*
 *
 *   signed ophptidy::page (signed c);
 *
 *   search for PHP source; ignore asp source; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ophptidy::page (signed c) 

{
	while (c != EOF) 
	{
		if (c == '<') 
		{
			c = ophptidy::feed (c);
			c = ophptidy::find (c);
			if (c == '!') 
			{
				c = ophptidy::context (c, '>');
				continue;
			}
			if (c == '%') 
			{
				c = ophptidy::context (c, '%', '>');
				continue;
			}
			if (c == '?') 
			{
				char string [256];
				char * cp = string;
				do 
				{
					* cp++ = c;
					c = std::cin.get ();
				}
				while (oascii::isalpha (c));
				* cp = (char) (0);
				std::cout << string;
				if (!strcmp (string, "?php")) 
				{
					c = ophptidy::program (c);
					continue;
				}
				if (!strcmp (string, "?xml")) 
				{
					c = ophptidy::context (c, '?', '>');
					continue;
				}
				continue;
			}
			while (oascii::isalpha (c)) 
			{
				c = ophptidy::feed (c);
			}
			c = ophptidy::context (c, '>');
			continue;
		}
		c = ophptidy::feed (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed ophptidy::program (signed c);
 *
 *   format php markup using class ophptidy for support;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ophptidy::program (signed c) 

{
	ophptidy::space (1);
	ophptidy::level (0);
	while (c != EOF) 
	{
		if (oascii::isspace (c)) 
		{
			do { c = std::cin.get (); } while (oascii::isspace (c));
			std::cout.put (' ');
			continue;
		}
		if (oascii::isquote (c))
		{
			c = ophptidy::literal (c);
			continue;
		}
		if (c == '?') 
		{
			c = std::cin.get ();
			if (c == '>') 
			{
				ophptidy::newline ();
				std::cout.put (' ');
				std::cout.put ('?');
				break;
			}
			std::cout.put ('?');
			continue;
		}
		if (c == '#') 
		{
			ophptidy::endline ();
			do 
			{
				c = ophptidy::command ('#', '\n');
			}
			while (c == '#');
			ophptidy::space (1);
			continue;
		}
		if (c == '/') 
		{
			ophptidy::endline ();
			c = ophptidy::comment (c);
			ophptidy::space (1);
			continue;
		}
		if (c == '{') 
		{

#if 0

			c = ophptidy::feed (c);
			c = ophptidy::find (c);
			ophptidy::increment ();

#else

			if (!this->mlevel) 
			{
				ophptidy::endline (1);
			}
			ophptidy::endline (1);
			ophptidy::newline ();
			ophptidy::increment ();
			c = ophptidy::feed (c);
			c = ophptidy::find (c);

#endif

			ophptidy::space (1);
			continue;
		}
		if (c == '}') 
		{
			ophptidy::decrement ();
			ophptidy::endline (1);
			ophptidy::newline ();
			c = ophptidy::feed (c);
			c = ophptidy::find (c);
			if (!this->mlevel) 
			{
				ophptidy::endline (1);
			}
			ophptidy::space (2);
			continue;
		}
		if ((c == ',') || (c == ';') || (c == ':')) 
		{
			c = ophptidy::feed (c);
			c = ophptidy::find (c);
			ophptidy::space (2);
			continue;
		}
		ophptidy::endline (1);
		c = ophptidy::statement (c);
		ophptidy::space (2);
	}
	c = ophptidy::feed (c);
	return (c);
}

/*====================================================================*
 *
 *   signed ophptidy::statement (signed c);
 *   
 *--------------------------------------------------------------------*/

signed ophptidy::statement (signed c) 

{
	if (isalpha (c) || (c == '_')) 
	{
		char string [512];
		char * cp = string;
		do 
		{
			* cp++ = c;
			c = std::cin.get ();
		}
		while (oascii::isalnum (c) || (c == '_'));
		* cp = (char) (0);
		if (!std::strcmp (string, "case")) 
		{
			ophptidy::newline (this->mlevel-1);
			std::cout << string;
			c = ophptidy::context (c, ':');
		}
		else if (!std::strcmp (string, "default")) 
		{
			ophptidy::newline (this->mlevel-1);
			std::cout << string;
			c = ophptidy::context (c, ':');
		}
		else 
		{
			ophptidy::newline (this->mlevel);
			std::cout << string;
			if ((c == '(') || (c == '[') || (c == '{')) 
			{
				std::cout.put (' ');
			}
			c = ophptidy::context (c, ",;{}?#");
		}
	}
	else 
	{
		ophptidy::newline (this->mlevel);
		c = ophptidy::context (c, ",;{}?#");
	}
	return (c);
}

/*====================================================================*
 *
 *   signed context (signed o, char const *charset); 
 *
 *   read stdin and buffer characters until one of the chracters in
 *   charset is read; return that character as the function value;
 *
 *   this function essentially collects an entire statement in the
 *   buffer; it is similar to other context methods but checks for 
 *   multiple terminators instead of one and returns the terminator
 *   instead of the following character;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ophptidy::context (signed c, char const * charset) 

{
	while ((c) && !std::strchr (charset, c) && (c != EOF)) 
	{
		c = ophptidy::context (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed context (signed c, signed o, signed e);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ophptidy::context (signed c, signed o, signed e) 

{
	c = ophptidy::feed (c);
	c = ophptidy::context_ (c, o, e);
	c = ophptidy::feed (c);
	return (c);
}

signed ophptidy::context_ (signed c, signed o, signed e) 

{
	while ((c != e) && (c != EOF)) 
	{
		c = ophptidy::context_ (c, o);
		c = ophptidy::feed (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed context (signed c, signed e); 
 *
 *   read and buffer nested expressions and literals until character
 *   (e) is encountered; buffer (e) and return the next character; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ophptidy::context (signed c, signed e) 

{
	c = ophptidy::feed (c);
	c = ophptidy::find (c);
	c = ophptidy::context_ (c, e);
	c = ophptidy::feed (c);
	return (c);
}

signed ophptidy::context_ (signed c, signed e) 

{
	while ((c != e) && (c != EOF)) 
	{
		c = ophptidy::context (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed context (signed  c); 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ophptidy::context (signed c) 

{
	if (oascii::isspace (c)) 
	{
		c = ophptidy::find (c);
		if ((c == ',') || (c == ';')) 
		{
			return (c);
		}
		if ((c == ':') || (c == '?')) 
		{
			return (c);
		}
		if ((c == ')') || (c == ']') || (c == '}')) 
		{
			return (c);
		}
		std::cout.put (' ');
	}
	else if ((c == ',') || (c == ';') || (c == '?')) 
	{
		c = ophptidy::feed (c);
		c = ophptidy::find (c);
		std::cout.put (' ');
	}
	else if (oascii::isdigit (c)) 
	{
		do 
		{
			c = ophptidy::feed (c);
		}
		while (oascii::isdigit (c) || (c == '.'));
	}
	else if (oascii::isalpha (c)) 
	{
		do 
		{
			c = ophptidy::feed (c);
		}
		while (oascii::isalnum (c) || (c == '_'));
		if ((c == '(') || (c == '[') || (c == '{')) 
		{
			std::cout.put (' ');
		}
	}
	else if (oascii::isquote (c)) 
	{
		c = ophptidy::literal (c);
	}
	else if (c == '/') 
	{
		c = ophptidy::comment (c);
	}
	else if (c == '{') 
	{
		c = ophptidy::context ('{', '}');
	}
	else if (c == '[') 
	{
		c = ophptidy::context ('[', ']');
	}
	else if (c == '(') 
	{
		c = ophptidy::context ('(', ')');
	}
	else 
	{
		c = ophptidy::feed (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed find (signed c);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ophptidy::find (signed c) 

{
	while (oascii::isspace (c)) 
	{
		c = std::cin.get ();
	}
	return (c);
}

/*====================================================================*
 *
 *   ophptidy()
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ophptidy::ophptidy () 

{
	return;
}

/*====================================================================*
 *
 *   ~ophptidy()
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ophptidy::~ophptidy () 

{
	return;
}

/*====================================================================*
 *   end definition
 *--------------------------------------------------------------------*/

#endif

