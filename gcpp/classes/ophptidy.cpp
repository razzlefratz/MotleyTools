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
			c = ophptidy::keep (c);
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
				char string [100];
				char *cp = string;
				do 
				{
					*cp++ = c;
					c = std::cin.get ();
				}
				while (oascii::isalpha (c));
				*cp = (char) (0);
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
				c = ophptidy::keep (c);
			}
			c = ophptidy::context (c, '>');
			continue;
		}
		c = ophptidy::keep (c);
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
	signed level = 0;
	signed space = 1;
	while (c != EOF) 
	{
		if (oascii::isspace (c)) 
		{
			c = std::cin.get ();
			continue;
		}
		if (c == '?') 
		{
			c = std::cin.get ();
			if (c == '>') 
			{
				std::cout.put ('\n');
				std::cout.put (' ');
				std::cout.put ('?');
				break;
			}
			std::cout.put ('?');
			continue;
		}
		if (c == '#') 
		{
			ophptidy::space (space);
			do 
			{
				c = ophptidy::command ('#', '\n');
			}
			while (c == '#');
			space = 1;
			continue;
		}
		if (c == '/') 
		{
			ophptidy::space (space);
			c = ophptidy::comment (c);
			space = 1;
			continue;
		}
		if (c == '{') 
		{

#if 0

			c = ophptidy::keep (c);
			c = ophptidy::find (c);
			level++;

#else

			if (!level) 
			{
				ophptidy::space (1);
			}
			ophptidy::space (1);
			ophptidy::level (level++);
			c = ophptidy::keep (c);
			c = ophptidy::find (c);

#endif

			space = 1;
			continue;
		}
		if (c == '}') 
		{
			ophptidy::space (1);
			ophptidy::level (--level);
			c = ophptidy::keep (c);
			c = ophptidy::find (c);
			if (!level) 
			{
				ophptidy::space (1);
			}
			space = 2;
			continue;
		}
		if ((c == ',') || (c == ';') || (c == ':')) 
		{
			c = ophptidy::keep (c);
			c = ophptidy::find (c);
			space = 2;
			continue;
		}
		ophptidy::space (1);
		c = ophptidy::statement (c, level, space);
		space = 2;
	}
	c = ophptidy::keep (c);
	return (c);
}


/*====================================================================*
 *
 *   signed ophptidy::statement (signed c, signed level, signed space);
 *   
 *--------------------------------------------------------------------*/

signed ophptidy::statement (signed c, signed level, signed space) 

{
	if (isalpha (c) || (c == '_')) 
	{
		char string [512];
		char *cp = string;
		do 
		{
			*cp++ = c;
			c = std::cin.get ();
		}
		while (oascii::isalnum (c) || (c == '_'));
		*cp = (char) (0);
		if (!std::strcmp (string, "case")) 
		{
			ophptidy::level (level-1);
			std::cout << string;
			c = ophptidy::context (c, ':');
		}
		else if (!std::strcmp (string, "default")) 
		{
			ophptidy::level (level-1);
			std::cout << string;
			c = ophptidy::context (c, ':');
		}
		else 
		{
			ophptidy::level (level);
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
		ophptidy::level (level);
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
	c = ophptidy::keep (c);
	c = ophptidy::inner_context (c, o, e);
	c = ophptidy::keep (c);
	return (c);
}

signed ophptidy::inner_context (signed c, signed o, signed e) 

{
	while ((c != e) && (c != EOF)) 
	{
		c = ophptidy::inner_context (c, o);
		c = ophptidy::keep (c);
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
	c = ophptidy::keep (c);
	c = ophptidy::find (c);
	c = ophptidy::inner_context (c, e);
	c = ophptidy::keep (c);
	return (c);
}

signed ophptidy::inner_context (signed c, signed e) 

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
		c = ophptidy::keep (c);
		c = ophptidy::find (c);
		std::cout.put (' ');
	}
	else if (oascii::isdigit (c)) 
	{
		do 
		{
			c = ophptidy::keep (c);
		}
		while (oascii::isdigit (c) || (c == '.'));
	}
	else if (oascii::isalpha (c)) 
	{
		do 
		{
			c = ophptidy::keep (c);
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
		c = ophptidy::keep (c);
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

