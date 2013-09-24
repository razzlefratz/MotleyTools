/*====================================================================*
 *
 *   octidy.cpp - definition of octidy class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCTIDY_SOURCE
#define oCTIDY_SOURCE

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
#include "../classes/octidy.hpp"

/*====================================================================*
 *   class variables;        
 *--------------------------------------------------------------------*/

ocexitwords octidy::exitwords;

/*====================================================================*
 *
 *   signed program (signed c);
 *
 *   format a source code file; 
 *
 *--------------------------------------------------------------------*/

signed octidy::program(signed c)

{
	oindent::level(0);
	oindent::space(0);
	while (c != EOF)
	{
		c = osource::find(c);
		if (c == '#')
		{
			oindent::endline();
			oinclude::header();
			do 
			{
				c = osource::command(c, '\n');
			}
			while (c == '#');
			oindent::space(1);
			continue;
		}
		if (c == '/')
		{
			oindent::endline();
			do 
			{
				c = osource::comment(c);
			}
			while (c == '/');
			oindent::endline(1);
			oindent::space(1);
			continue;
		}
		if (c == '{')
		{
			if (! this->mlevel)
			{
				oindent::endline(1);
			}
			oindent::endline(1);
			oindent::newline();
			c = osource::keep(c);
			oindent::increment();
			oindent::space(2);
			continue;
		}
		if (c == '}')
		{
			oindent::decrement();
			oindent::endline(1);
			oindent::newline();
			do 
			{
				c = osource::keep(c);
				c = osource::find(c);
			}
			while ((c == ',') || (c == ';'));
			if (! this->mlevel)
			{
				oindent::endline(1);
				oindent::space(1);
			}
			else 
			{
				oindent::space(2);
			}
			continue;
		}
		if ((c == ',') || (c == ';') || (c == ':'))
		{
			c = osource::keep(c);
			c = osource::find(c);
			oindent::space(2);
			continue;
		}
		oindent::endline(1);
		c = octidy::statement(c);
		oindent::space(2);
	}
	oindent::endline();
	oinclude::footer();
	return (c);
}

/*====================================================================*
 *
 *   signed atheros (signed c);
 *
 *--------------------------------------------------------------------*/

signed octidy::atheros(signed c)

{
	oindent::level(0);
	oindent::space(0);
	while (c != EOF)
	{
		c = osource::find(c);
		if (c == '#')
		{
			oindent::endline();
			oinclude::header();
			do 
			{
				c = osource::command(c);
			}
			while (c == '#');
			oindent::space(1);
			continue;
		}
		if (c == '/')
		{
			oindent::endline();
			do 
			{
				c = osource::comment(c);
			}
			while (c == '/');
			oindent::endline(1);
			oindent::space(1);
			continue;
		}
		if (c == '{')
		{
			if (! this->mlevel)
			{
				oindent::endline(2);
				oindent::newline();
			}
			c = osource::keep(c);
			oindent::increment();
			oindent::space(1);
			continue;
		}
		if (c == '}')
		{
			oindent::decrement();
			oindent::endline(1);
			oindent::newline();
			do 
			{
				c = osource::keep(c);
				c = osource::find(c);
			}
			while ((c == ',') || (c == ';'));
			if (! this->mlevel)
			{
				oindent::endline(1);
				oindent::space(1);
			}
			else 
			{
				oindent::space(2);
			}
			continue;
		}
		if ((c == ',') || (c == ';') || (c == ':'))
		{
			c = osource::keep(c);
			c = osource::find(c);
			oindent::space(2);
			continue;
		}
		oindent::endline(1);
		c = octidy::statement(c);
		oindent::space(2);
	}
	oindent::endline();
	oinclude::footer();
	return (c);
}

/*====================================================================*
 *
 *   signed charlie (signed c);
 *
 *   this method is similar method program() but annotates comments 
 *   and inserts include guards; essentially, this is charlie's own
 *   private formatter;
 *
 *--------------------------------------------------------------------*/

signed octidy::charlie(signed c)

{
	oindent::level(0);
	oindent::space(0);
	c = ocomment::preamble(c);
	while (c != EOF)
	{
		c = osource::find(c);
		if (c == '#')
		{
			oindent::endline();
			oinclude::header();
			do 
			{
				c = osource::command(c);
			}
			while (c == '#');
			oindent::space(1);
			continue;
		}
		if (c == '/')
		{
			oindent::endline();
			do 
			{
				c = ocomment::comment(c);
			}
			while (c == '/');
			oindent::space(1);
			continue;
		}
		if (c == '{')
		{
			if (! this->mlevel)
			{
				oindent::endline(1);
			}
			oindent::endline(1);
			oindent::newline();
			c = osource::keep(c);
			oindent::increment();
			oindent::space(2);
			continue;
		}
		if (c == '}')
		{
			oindent::decrement();
			oindent::endline(1);
			oindent::newline();
			do 
			{
				c = osource::keep(c);
				c = osource::find(c);
			}
			while ((c == ',') || (c == ';'));
			if (! this->mlevel)
			{
				oindent::endline(1);
				c = ocomment::preamble(c);
				oindent::space(1);
			}
			else 
			{
				oindent::space(2);
			}
			continue;
		}
		if ((c == ',') || (c == ';') || (c == ':'))
		{
			c = osource::keep(c);
			c = osource::find(c);
			oindent::space(2);
			continue;
		}
		oindent::endline(1);
		c = octidy::statement(c);
		oindent::space(2);
	}
	oindent::endline();
	oinclude::footer();
	return (c);
}

/*====================================================================*
 *
 *   signed statement (signed c); 
 *
 *--------------------------------------------------------------------*/

signed octidy::statement(signed c)

{
	char const * charset = ",;{}#";
	char string[512];
	char * sp = string;
	while (oascii::isalnum(c) || (c == '_'))
	{
		if ((sp - string) <= (signed) (sizeof(string) - 1))
		{
			* sp++ = c;
		}
		c = std::cin.get();
		if (c == EOF)
		{
			return (c);
		}
	}
	c = osource::find(c);
	* sp = (char) (0);
	if (sp == string)
	{
		oindent::print(this->mlevel, 0, string);
		c = octidy::context(c, charset);
	}
	else if(! std::strcmp(string, "class"))
	{
		oindent::print(this->mlevel, 0, string);
		std::cout.put(' ');
		c = octidy::context(c, "{");
	}
	else if(octidy::exitwords.defined(string))
	{
		oindent::print(this->mlevel, 0, string);
		if (c == '(')
		{
			std::cout.put(' ');
			c = octidy::context(c, charset);
		}
		else if(c != ';')
		{
			std::cout.put(' ');
			std::cout.put('(');
			c = octidy::context(c, ";");
			std::cout.put(')');
		}
	}
	else if(! std::strcmp(string, "case"))
	{
		oindent::print(this->mlevel - 1, 0, string);
		std::cout.put(' ');
		c = octidy::context(c, ":");
	}
	else if(c == ':')
	{
		if (c == std::cin.peek())
		{
			oindent::print(this->mlevel, 0, string);
			c = osource::keep(c);
			c = osource::keep(c);
			c = octidy::context(c, charset);
		}
		else 
		{
			oindent::print(this->mlevel - 1, 0, string);
			c = osource::keep(c);
			c = osource::find(c);
			std::cout.put(' ');
		}
	}
	else 
	{
		oindent::print(this->mlevel, 0, string);
		c = osource::terminate(c);
		c = octidy::context(c, charset);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed context (signed c, char const * charset) const; 
 *
 *--------------------------------------------------------------------*/

signed octidy::context(signed c, char const * charset) const

{
	while ((c) && (c != EOF) && ! std::strchr(charset, c))
	{
		c = octidy::context(c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed context (signed c, signed o, signed e) const;
 *
 *--------------------------------------------------------------------*/

signed octidy::context(signed c, signed o, signed e) const

{
	c = osource::keep(c);
	c = osource::find(c);
	c = octidy::_context(c, o, e);
	c = osource::keep(c);
	return (c);
}

signed octidy::_context(signed c, signed o, signed e) const

{
	while ((c != e) && (c != EOF))
	{
		c = octidy::_context(c, o);
		c = osource::keep(c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed context (signed c, signed e) const; 
 *
 *--------------------------------------------------------------------*/

signed octidy::context(signed c, signed e) const

{
	c = osource::keep(c);
	c = osource::find(c);
	c = octidy::_context(c, e);
	c = osource::keep(c);
	return (c);
}

signed octidy::_context(signed c, signed e) const

{
	while ((c != e) && (c != EOF))
	{
		c = octidy::context(c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed context (signed  c) const; 
 *
 *--------------------------------------------------------------------*/

signed octidy::context(signed c) const

{
	if (c == '\\')
	{
		signed o;
		o = osource::keep(c);
		c = osource::keep(o);
		c = osource::find(c);
		if (o == '\n')
		{
			oindent::print(oindent::margin(), oindent::offset(), oindent::level());
		}
	}
	else if(c == '(')
	{
		c = octidy::context(c, ')');
		c = octidy::terminate(c);
	}
	else if(c == '[')
	{
		c = octidy::context(c, ']');
		c = octidy::terminate(c);
	}
	else if(c == '{')
	{
		c = octidy::context(c, '}');
		c = octidy::terminate(c);
	}
	else 
	{
		c = osource::operate(c);
	}
	return (c);
}

/*====================================================================*
 *
 *   octidy (void)
 *
 *--------------------------------------------------------------------*/

octidy::octidy(void)

{
	return;
}

/*====================================================================*
 *
 *   ~ octidy (void)
 *
 *--------------------------------------------------------------------*/

octidy::~ octidy(void)

{
	return;
}

/*====================================================================*
 *   end definition
 *--------------------------------------------------------------------*/

#endif



