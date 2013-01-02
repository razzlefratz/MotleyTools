/*====================================================================*
 *
 *   oxml.cpp - implementation of the oxml class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oXML_SOURCE
#define oXML_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdio>
#include <cstring>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oxml.hpp"
#include "../classes/oascii.hpp"

/*====================================================================*
 *
 *   signed page (signed c)
 *   
 *   format a page while leaving non-markup text alone;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed oxml::page (signed c) 

{
	while (c != EOF) 
	{
		if (c == '<') 
		{
			c = oxml::element (c);
			continue;
		}
		c = omarkup::keep (c);
	}
	return (c);
}


/*====================================================================*
 *
 *   signed element (signed c)
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed oxml::element (signed c) 

{
	c = otidy::pack (c);
	if (c == '!') 
	{
		c = omarkup::sgml (c);
	}
	else if (c == '%') 
	{
		c = omarkup::context (c, '%', '>');
	}
	else if (c == '?') 
	{
		c = omarkup::context (c, '?', '>');
	}
	else if ((c != '/') && (c != EOF)) 
	{
		c = oxml::xml (c);
	}
	return (c);
}


/*====================================================================*
 *
 *   signed xml (signed c);
 *   
 *   element[ attribute[=value]][ attribute[=value]][/]
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed oxml::xml (signed c) 

{
	if (oascii::isalpha (c)) 
	{
		c = omarkup::nmtoken (c);
	}
	else if (oascii::isquote (c)) 
	{
		c = omarkup::enquote (c, c);
	}
	else 
	{
		c = omarkup::unknown (c);
	}
	this->melement = otext::replace (this->melement, this->mstring);
	std::cout << this->melement;
	c = otidy::next (c);
	while ((c != '/') && (c != '>') && (c != EOF)) 
	{
		std::cout.put (' ');
		if (oascii::isalpha (c)) 
		{
			c = omarkup::nmtoken (c);
		}
		else if (oascii::isquote (c)) 
		{
			c = omarkup::enquote (c, c);
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
			c = otidy::pack (c);
			if (oascii::isquote (c)) 
			{
				c = omarkup::dequote (c, c);
			}
			else 
			{
				c = omarkup::unknown (c);
			}
			this->mvalue = otext::replace (this->mvalue, this->mstring);
			std::cout.put (this->mquote);
			std::cout << this->mvalue;
			std::cout.put (this->mquote);
			c = otidy::next (c);
		}
	}
	c = oxml::content (c);
	c = otidy::pack (c);
	while (oascii::nmtoken (c)) 
	{
		c = omarkup::keep (c);
	}
	c = otidy::next (c);
	return (c);
}


/*====================================================================*
 *
 *   signed content (signed c)
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed oxml::content (signed c) 

{
	while ((c != '/') && (c != EOF)) 
	{
		while ((c != '<') && (c != EOF)) 
		{
			c = omarkup::keep (c);
		}
		c = oxml::element (c);
	}
	return (c);
}


/*====================================================================*
 *
 *   oxml()
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oxml::oxml () 

{
	return;
}


/*====================================================================*
 *
 *   ~oxml()
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oxml::~oxml () 

{
	return;
}


/*====================================================================*
 *   end implementation
 *--------------------------------------------------------------------*/

#endif

