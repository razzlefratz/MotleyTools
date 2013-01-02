/*====================================================================*
 *
 *   omarkup.cpp - implementation of the omarkup class.
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

#include <cstring>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/omarkup.hpp"

/*====================================================================*
 *   variables;        
 *--------------------------------------------------------------------*/

#ifdef oHTMLEMPTY_HEADER

oHTMLEmpty omarkup::htmlempty;

#endif

/*====================================================================*
 *
 *   signed omarkup::level () const;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed omarkup::level () const 

{
	return (this->mlevel);
}


/*====================================================================*
 *   
 *   char const * element () const;
 *   char const * attribute () const 
 *   char const * value () const 
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * omarkup::element () const 

{
	return ((char const *) (this->melement));
}

char const * omarkup::attribute () const 

{
	return ((char const *) (this->mattribute));
}

char const * omarkup::value () const 

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

char omarkup::quote () const 

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

omarkup & omarkup::quote (signed quote) 

{
	this->mquote = quote;
	return (*this);
}


/*====================================================================*
 *
 *   signed indent (signed c) const ;
 *
 *   indent a markup file;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed omarkup::indent (signed c) 

{
	this->mspace = 1;
	this->mlevel = 0;
	this->mcount = 0;
	while (c != EOF) 
	{
		if (c == '<') 
		{
			if (this->mcount) 
			{
				oindent::space (this->mspace);
				oindent::level (this->mlevel);
			}
			c = otidy::find (c);
			if (c == '!') 
			{
				c = omarkup::sgml (c);
				continue;
			}
			if (c == '?') 
			{
				c = omarkup::nmtoken (c);
				std::cout << this->mstring;
				if (!std::strcmp (this->mstring, "?xml")) 
				{
					c = omarkup::process (c);
					continue;
				}
				if (!std::strcmp (this->mstring, "?php")) 
				{
					c = omarkup::php (c);
					continue;
				}
				c = omarkup::php (c);
				continue;
			}
			if (c == '%') 
			{
				c = omarkup::asp (c);
				continue;
			}
			c = omarkup::xhtml (c);
			continue;
		}
		if (c == '>') 
		{
			c = otidy::find (c);
			oindent::space (this->mspace);
			oindent::level (this->mlevel);
			this->mcount = 0;
			continue;
		}
		c = omarkup::cdata (c, '<');
		this->mcount++;
	}
	return (c);
}


/*====================================================================*
 *
 *   signed process (signed c) const;
 *
 *   read and write processing instruction with basic formatting up
 *   to and including the trailing '?'; return the terminating '>';
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed omarkup::process (signed c) const 

{
	c = otidy::context (c, '?', '>');
	return (c);
}


/*====================================================================*
 *
 *   signed sgml (signed c) const;
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

signed omarkup::sgml (signed c) const 

{
	c = otidy::find (c);
	if (c == '-') 
	{
		c = omarkup::comment (c);
	}
	else if (c == '[') 
	{
		c = otidy::find (c);
		while (oascii::isalpha (c)) 
		{
			c = otidy::keep (c);
		}
		c = otidy::next (c);
		if (c == '[') 
		{
			c = otidy::consume (c, ']', ']');
		}
	}
	else if (oascii::isalpha (c)) 
	{
		do 
		{
			c = oascii::toupper (c);
			c = otidy::keep (c);
		}
		while (oascii::isalpha (c) || (c == '-'));
	}
	c = otidy::find (c);
	while ((c != '<') && (c != '>') && (c != EOF)) 
	{
		std::cout.put (' ');
		if (c == '-') 
		{
			c = omarkup::comment (c);
		}
		else if (c == '(') 
		{
			c = omarkup::context ('(', ')');
			if ((c == '*') || (c == '+')) 
			{
				c = otidy::keep (c);
			}
		}
		else if (c == '[') 
		{
			c = omarkup::context ('[', ']');
		}
		else if (oascii::isquote (c)) 
		{
			c = otidy::literal (c);
		}
		else if (oascii::isalpha (c) || (c == '#') || (c == '%')) 
		{
			do 
			{
				c = otidy::keep (c);
			}
			while (oascii::isalnum (c) || (c == '-') || (c == '.'));
		}
		else if (oascii::isdigit (c)) 
		{
			do 
			{
				c = otidy::keep (c);
			}
			while (oascii::isdigit (c) || (c == '.'));
		}
		else 
		{
			c = omarkup::keep (c);
		}
		c = otidy::next (c);
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

signed omarkup::xhtml (signed c) 

{
	if (c == '/') 
	{
		c = otidy::find (c);
		this->mlevel--;
		this->mlevel--;
	}
	if (oascii::isalpha (c)) 
	{
		c = omarkup::nmtoken (c);
	}
	else if (oascii::isdigit (c)) 
	{
		c = omarkup::number (c);
	}
	else if (oascii::isquote (c)) 
	{
		c = otidy::literal (c);
	}
	else 
	{
		c = omarkup::unknown (c);
	}
	this->melement = otext::replace (this->melement, this->mstring);
	std::cout << this->melement;
	c = otidy::next (c);
	while ((c != '<') && (c != '/') && (c != '>') && (c != EOF)) 
	{
		std::cout.put (' ');
		if (oascii::isalpha (c)) 
		{
			c = omarkup::nmtoken (c);
		}
		else if (oascii::isdigit (c)) 
		{
			c = omarkup::number (c);
		}
		else if (oascii::isquote (c)) 
		{
			c = omarkup::literal (c);
		}
		else 
		{
			c = omarkup::unknown (c);
		}
		this->mattribute = otext::replace (this->mattribute, this->mstring);
		std::cout << this->mattribute;
		c = otidy::next (c);
		if (c == '=') 
		{
			c = otidy::find (c);
			if (oascii::isquote (c)) 
			{
				c = omarkup::dequote (c);
			}
			else 
			{
				c = omarkup::unknown (c);
			}
			this->mvalue = otext::replace (this->mvalue, this->mstring);
			c = otidy::next (c);
			std::cout.put (this->mquote);
			std::cout << this->mvalue;
			std::cout.put (this->mquote);
		}
	}
	if (c == '/') 
	{
		c = otidy::find (c);
		this->mlevel--;
	}
	else if (omarkup::htmlempty.defined (this->melement)) 
	{
		if (omarkup::anyset (oMARKUP_REPAIR)) 
		{
			std::cout.put ('/');
			this->mlevel--;
		}
	}
	this->mlevel++;
	return (c);
}


/*====================================================================*
 *
 *   signed php (signed c) const;
 *
 *   read and write php script without any formatting; include the
 *   terminating "?>" and return the following character'
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed omarkup::php (signed c) const 

{
	c = otidy::collect (c, '?', '>');
	return (c);
}


/*====================================================================*
 *
 *   signed asp (signed c) const;
 *   
 *   read and write asp script without any formatting; include the
 *   terminating "%>" and return the following character;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed omarkup::asp (signed c) const 

{
	c = otidy::collect (c, '%', '>');
	return (c);
}


/*====================================================================*
 *
 *   signed number (char buffer [], size_t length, unsigned flags);
 *   
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed omarkup::number (signed c) 

{
	char * string = this->mstring;
	do 
	{
		*string++ = c;
		c = std::cin.get ();
	}
	while (oascii::isdigit (c) || (c == '.'));
	*string = (char) (0);
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

signed omarkup::nmtoken (signed c) 

{
	char * string = this->mstring;
	do 
	{
		*string++ = c;
		c = std::cin.get ();
	}
	while (oascii::nmtoken (c));
	*string = (char) (0);
	return (c);
}


/*====================================================================*
 *
 *   signed cdata (signed c, signed e) const;
 *   
 *   read and write cdata;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed omarkup::cdata (signed c, signed e) const 

{
	signed space = 0;
	while ((c != e) && (c != EOF)) 
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
		c = otidy::keep (c);
	}
	return (e);
}


/*====================================================================*
 *
 *   signed dequote (signed e) 
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed omarkup::dequote (signed e) 

{
	char * string = this->mstring;
	int c = std::cin.get ();
	while ((c != e) && (c != EOF)) 
	{
		*string++ = c;
		c = std::cin.get ();
	}
	*string = (char) (0);
	c = std::cin.get ();
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

signed omarkup::comment (signed c) const 

{
	c = otidy::keep (c);
	if (c == '-') 
	{
		while (c == '-') 
		{
			c = otidy::keep (c);
		}
		while ((c != '-') && (c != EOF)) 
		{
			while ((c != '-') && (c != EOF)) 
			{
				c = otidy::keep (c);
			}
			c = otidy::keep (c);
		}
		while (c == '-') 
		{
			c = otidy::keep (c);
		}
	}
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

signed omarkup::unknown (signed c) 

{
	char * string = this->mstring;
	while (!isspace (c) && (c != '<') && (c != '=') && (c !='/') && (c != '?') && (c != '>')) 
	{
		*string++ = c;
		c = std::cin.get ();
	}
	*string = (char) (0);
	return (c);
}


/*====================================================================*
 *
 *   signed control (signed c) const
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed omarkup::control (signed c) const 

{
	c = otidy::find (c);
	while ((c != '/') && (c != EOF)) 
	{
		if (c == '>') 
		{
			c = otidy::keep (c);
			c = omarkup::content (c);
			return (c);
		}
		if (oascii::isspace (c)) 
		{
			c = otidy::keep (' ');
			continue;
		}
		if (oascii::nmtoken (c)) 
		{
			do 
			{
				c = otidy::keep (c);
			}
			while (oascii::nmtoken (c));
			continue;
		}
		if (c == '-') 
		{
			c = otidy::comment (c);
			continue;
		}
		if (oascii::isquote (c)) 
		{
			c = otidy::literal (c);
			continue;
		}
		c = otidy::keep (c);
	}
	c = otidy::consume (c, '>');
	return (c);
}


/*====================================================================*
 *
 *   signed content (signed c) const
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed omarkup::content (signed c) const 

{
	while ((c != '/') && (c != EOF)) 
	{
		while ((c != '<') && (c != EOF)) 
		{
			c = otidy::keep (c);
		}
		c = omarkup::control (c);
	}
	return (c);
}


/*====================================================================*
 *
 *   omarkup()
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

omarkup::omarkup () 

{
	this->mstring = new char [1024];
	this->mstring [0] = (char) (0);
	this->melement = otext::save ("");
	this->mattribute = otext::save ("");
	this->mvalue = otext::save ("");
	this->mquote = '\"';
	this->mspace = 1;
	this->mlevel = 0;
	this->mcount = 0;
	return;
}


/*====================================================================*
 *
 *   ~omarkup()
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

omarkup::~omarkup () 

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

