/*====================================================================*
 *
 *   ohtmltidy.cpp - implementation of the ohtmltidy class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oMARKUP_SOURCE
#define oMARKUP_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdio>
#include <cstring>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ohtmltidy.hpp"
#include "../classes/oindent.hpp"
#include "../classes/oascii.hpp"

/*====================================================================*
 *   class variables;        
 *--------------------------------------------------------------------*/

oHTMLEmpty ohtmltidy::htmlempty;

/*====================================================================*
 *   
 *   char const * element () const;
 *   char const * attribute () const 
 *   char const * value () const 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * ohtmltidy::element () const 

{
	return ((char const *) (this->melement));
}

char const * ohtmltidy::attribute () const 

{
	return ((char const *) (this->mattribute));
}

char const * ohtmltidy::value () const 

{
	return ((char const *) (this->mvalue));
}

/*====================================================================*
 *
 *   char quote () const;
 *
 *   return the default quote character value;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char ohtmltidy::quote () const 

{
	return (this->mquote);
}

/*====================================================================*
 *
 *   char quote (char quote);
 *
 *   define the default quote character value; attribute values are
 *   enclosed in this value by default;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ohtmltidy & ohtmltidy::quote (signed quote) 

{
	this->mquote = quote;
	return (* this);
}

/*====================================================================*
 *
 *   signed page (signed c);
 *
 *   indent a markup file;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ohtmltidy::page (signed c) 

{
	this->mspace = 1;
	this->mlevel = 0;
	while (c != EOF) 
	{
		if (c == '<') 
		{
			c = ohtmltidy::keep (c);
			c = ohtmltidy::find (c);
			if (c == '?') 
			{
				c = ohtmltidy::context (c, '?', '>');
			}
			else if (c == '%') 
			{
				c = ohtmltidy::context (c, '%', '>');
			}
			else if (c == '!') 
			{
				c = ohtmltidy::sgml (c);
			}
			else 
			{
				c = ohtmltidy::xhtml (c);
			}
			c = ohtmltidy::find (c);
		}
		else 
		{
			c = ohtmltidy::cdata (c);
		}
		oindent::space (this->mspace);
		oindent::level (this->mlevel);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed xml (signed c) const
 *
 *   read and write an entire <?xml ... ?> segment including opening
 *   and closing brackets;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ohtmltidy::xml (signed c) const 

{
	c = ohtmltidy::context (c, '?', '>');
	return (c);
}

/*====================================================================*
 *
 *   signed ohtmltidy::php (signed c);
 *
 *   read and write an entire <?php ... ?> segment including opening
 *   and closing brackets;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ohtmltidy::php (signed c) const 

{
	c = ohtmltidy::context (c, '?', '>');
	return (c);
}

/*====================================================================*
 *
 *   signed asp (signed c) const
 *   
 *   read and write entire <% ... %> asp segment including opening
 *   and closing brackets;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ohtmltidy::asp (signed c) const 

{
	c = ohtmltidy::context (c, '%', '>');
	return (c);
}

/*====================================================================*
 *
 *   signed sgml (signed c);
 *
 *	<!AAA ... >
 *	<!-- ... -->
 *	<![NAME[ ... ]]>
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ohtmltidy::sgml (signed c) 

{
	if (c == '<') 
	{
		c = ohtmltidy::keep (c);
		c = ohtmltidy::find (c);
	}
	if (c == '!') 
	{
		c = ohtmltidy::keep (c);
		c = ohtmltidy::find (c);
	}
	if (c == '-') 
	{
		c = ohtmltidy::comment (c);
	}
	else if (c == '[') 
	{
		c = ohtmltidy::keep (c);
		c = ohtmltidy::find (c);
		do 
		{
			c = oascii::toupper (c);
			c = ohtmltidy::keep (c);
		}
		while (oascii::isalpha (c) || (c == '-'));
		c = ohtmltidy::find (c);
		c = ohtmltidy::content (c, ']', ']');
	}
	else if (oascii::isalpha (c)) 
	{
		do 
		{
			c = oascii::toupper (c);
			c = ohtmltidy::keep (c);
		}
		while (oascii::isalpha (c) || (c == '-'));
	}
	c = ohtmltidy::find (c);
	while ((c != '<') && (c != '>') && (c != EOF)) 
	{
		std::cout.put (' ');
		if (c == '-') 
		{
			c = ohtmltidy::comment (c);
		}
		else if (c == '(') 
		{
			c = ohtmltidy::context ('(', ')');
			if ((c == '*') || (c == '+')) 
			{
				c = ohtmltidy::keep (c);
			}
		}
		else if (c == '[') 
		{
			c = ohtmltidy::keep (c);
			c = ohtmltidy::find (c);
			do 
			{
				c = oascii::toupper (c);
				c = ohtmltidy::keep (c);
			}
			while (oascii::isalpha (c) || (c == '-'));
			c = ohtmltidy::find (c);
			c = ohtmltidy::content (c, ']', ']');
		}
		else if (oascii::isquote (c)) 
		{
			c = ohtmltidy::enquote (c, c);
		}
		else if (oascii::isalpha (c) || (c == '#') || (c == '%')) 
		{
			do 
			{
				c = oascii::toupper (c);
				c = ohtmltidy::keep (c);
			}
			while (oascii::isalnum (c) || (c == '-') || (c == '.'));
		}
		else if (oascii::isdigit (c)) 
		{
			do 
			{
				c = ohtmltidy::keep (c);
			}
			while (oascii::isdigit (c) || (c == '.'));
		}
		c = ohtmltidy::find (c);
	}
	if (c == '>') 
	{
		c = ohtmltidy::keep (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed xhtml (signed c);
 *   
 *   [/] element [ attribute [ = value ]] [ attribute [ = value]] [/]
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ohtmltidy::xhtml (signed c) 

{
	if (c == '<') 
	{
		c = ohtmltidy::keep (c);
		c = ohtmltidy::find (c);
	}
	if (c == '/') 
	{
		c = ohtmltidy::keep (c);
		c = ohtmltidy::find (c);
		this->mlevel--;
	}
	else 
	{
		this->mlevel++;
	}
	if (oascii::isalpha (c)) 
	{
		c = ohtmltidy::nmtoken (c);
	}
	else if (oascii::isquote (c)) 
	{
		c = ohtmltidy::enquote (c, c);
	}
	else 
	{
		c = ohtmltidy::unknown (c);
	}
	this->melement = otext::replace (this->melement, this->mstring);
	std::cout << this->melement;
	c = ohtmltidy::find (c);
	while ((c != '/') && (c != '>') && (c != EOF)) 
	{
		std::cout.put (' ');
		if (oascii::isalpha (c)) 
		{
			c = ohtmltidy::nmtoken (c);
		}
		else if (oascii::isquote (c)) 
		{
			c = ohtmltidy::enquote (c, c);
		}
		else 
		{
			c = ohtmltidy::unknown (c);
		}
		this->mattribute = otext::replace (this->mattribute, this->mstring);
		std::cout << this->mattribute;
		c = ohtmltidy::find (c);
		if (c == '=') 
		{
			c = ohtmltidy::keep (c);
			c = ohtmltidy::find (c);
			if (oascii::isquote (c)) 
			{
				c = ohtmltidy::dequote (c, c);
			}
			else 
			{
				c = ohtmltidy::unknown (c);
			}
			this->mvalue = otext::replace (this->mvalue, this->mstring);
			std::cout.put (this->mquote);
			std::cout << this->mvalue;
			std::cout.put (this->mquote);
			c = ohtmltidy::find (c);
		}
	}
	if (c == '/') 
	{
		c = ohtmltidy::keep (c);
		c = ohtmltidy::find (c);
		this->mlevel--;
	}
	else if (ohtmltidy::htmlempty.defined (this->melement)) 
	{
		if (ohtmltidy::anyset (oMARKUP_REPAIR)) 
		{
			std::cout.put ('/');
			this->mlevel--;
		}
	}
	if (c == '>') 
	{
		c = ohtmltidy::keep (c);
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

signed ohtmltidy::comment (signed c) const 

{
	c = ohtmltidy::keep (c);
	if (c == '-') 
	{
		while (c == '-') 
		{
			c = ohtmltidy::keep (c);
		}
		while ((c != '-') && (c != EOF)) 
		{
			while ((c != '-') && (c != EOF)) 
			{
				c = ohtmltidy::keep (c);
			}
			c = ohtmltidy::keep (c);
		}
		while (c == '-') 
		{
			c = ohtmltidy::keep (c);
		}
	}
	return (c);
}

/*====================================================================*
 *
 *   signed cdata (signed c) const;
 *   
 *   read and write cdata;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ohtmltidy::cdata (signed c) const 

{
	signed space = 0;
	while ((c != '<') && (c != EOF)) 
	{
		if (oascii::isspace (c)) 
		{
			c = std::cin.get ();
			space = 1;
			continue;
		}
		if (space) 
		{
			std::cout.put (' ');
			space = 0;
			continue;
		}
		c = ohtmltidy::keep (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed enquote (signed c, signed e) 
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ohtmltidy::enquote (signed c, signed e) 

{
	char * string = this->mstring;
	c = ohtmltidy::keep (this->mquote);
	while ((c != e) && (c != EOF)) 
	{
		* string++ = c;
		c = ohtmltidy::keep (c);
	}
	c = ohtmltidy::keep (this->mquote);
	* string = (char) (0);
	return (c);
}

/*====================================================================*
 *
 *   signed dequote (signed c, signed e) 
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ohtmltidy::dequote (signed c, signed e) 

{
	char * string = this->mstring;
	c = std::cin.get ();
	while ((c != e) && (c != EOF)) 
	{
		* string++ = c;
		c = std::cin.get ();
	}
	c = std::cin.get ();
	* string = (char) (0);
	return (c);
}

/*====================================================================*
 *
 *   signed nmtoken (signed c)
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ohtmltidy::nmtoken (signed c) 

{
	char * string = this->mstring;
	do 
	{
		* string++ = c;
		c = std::cin.get ();
	}
	while (oascii::nmtoken (c));
	* string = (char) (0);
	return (c);
}

/*====================================================================*
 *
 *   signed unknown (signed c);
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ohtmltidy::unknown (signed c) 

{
	char * string = this->mstring;
	while (!isspace (c) && (c != '<') && (c != '=') && (c !='/') && (c != '?') && (c != '>')) 
	{
		* string++ = c;
		c = std::cin.get ();
	}
	* string = (char) (0);
	return (c);
}

/*====================================================================*
 *   
 *   signed find (signed c) const;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ohtmltidy::find (signed c) const 

{
	while (oascii::isspace (c)) 
	{
		c = std::cin.get ();
	}
	return (c);
}

/*====================================================================*
 *   
 *   signed keep (signed c) const;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ohtmltidy::keep (signed c) const 

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
 *   ohtmltidy & print () 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ohtmltidy & ohtmltidy::print () 

{
	std::cout << this->mstring;
	return (* this);
}

/*====================================================================*
 *
 *   ohtmltidy()
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ohtmltidy::ohtmltidy () 

{
	this->mstring = new char [1024];
	this->mstring [0] = (char) (0);
	this->melement = otext::save ("");
	this->mattribute = otext::save ("");
	this->mvalue = otext::save ("");
	this->mquote = '\"';
	this->mspace = 1;
	this->mlevel = 0;
	return;
}

/*====================================================================*
 *
 *   ~ohtmltidy()
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ohtmltidy::~ohtmltidy () 

{
	delete [] this->mstring;
	delete [] this->melement;
	delete [] this->mattribute;
	delete [] this->mvalue;
	return;
}

/*====================================================================*
 *   end implementation
 *--------------------------------------------------------------------*/

#endif

