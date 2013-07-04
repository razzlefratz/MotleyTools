/*====================================================================*
 *
 *   oscanfile.cpp - implementation of the oscanfile class.
 *
 *   read from stdin; detect and return basic lexicons in various forms;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oSCANFILE_SOURCE
#define oSCANFILE_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstring>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oscanfile.hpp"
#include "../../gcc/tools/symbol.h"
#include "../../gcc/tools/sizes.h"

/*====================================================================*
 *
 *   bool end () const;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscanfile::end () const 

{
	return (std::cin.eof ());
}

/*====================================================================*
 *
 *   unsigned int character () const;
 *
 *   return the current character;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

unsigned int oscanfile::character () const 

{
	return (this->mbreak);
}

/*====================================================================*
 *
 *   size_t tokensize () const;
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

size_t oscanfile::tokensize () const 

{
	return (std::strlen (this->mtoken));
}

/*====================================================================*
 *
 *   char const *tokentext () const;
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * oscanfile::tokentext () const 

{
	return ((char const *) (this->mtoken));
}

/*====================================================================*
 *
 *   unsigned int tokentype () const;
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

unsigned int oscanfile::tokentype () const 

{
	return (this->mclass);
}

/*====================================================================*
 *
 *   oscanfile & tokentype (char c);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::tokentype (char c) 

{
	this->mclass = c;
	return (* this);
}

/*====================================================================*
 *
 *   bool isempty () const;
 *
 *   return logical true once the file is exhausted;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscanfile::isempty () const 

{
	return (this->mbreak == EOF);
}

/*====================================================================*
 *
 *   bool isbreak (unsigned c) const;
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscanfile::isbreak (signed c) const 

{
	return (this->mbreak == c);
}

/*====================================================================*
 *
 *   bool isbreak (char const * charset) const;
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscanfile::isbreak (char const * charset) const 

{
	return (std::strchr (charset, this->mbreak));
}

/*====================================================================*
 *
 *   bool isspace () const;
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscanfile::isspace () const 

{
	return (oascii::isspace (this->mbreak));
}

/*====================================================================*
 *
 *   bool isalpha () const;
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscanfile::isalpha () const 

{
	return (oascii::isalpha (this->mbreak));
}

/*====================================================================*
 *
 *   bool isalnum () const;
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscanfile::isalnum () const 

{
	return (oascii::isalnum (this->mbreak));
}

/*====================================================================*
 *
 *   bool isdigit () const;
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscanfile::isdigit () const 

{
	return (oascii::isdigit (this->mbreak));
}

/*====================================================================*
 *
 *   bool isident () const;
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscanfile::isident () const 

{
	return (oascii::isident (this->mbreak));
}

/*====================================================================*
 *
 *   bool isclass (unsigned c) const;
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscanfile::isclass (signed c) const 

{
	return (this->mclass == c);
}

/*====================================================================*
 *
 *   bool isclass (char const *charset) const;
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscanfile::isclass (char const * charset) const 

{
	return (std::strchr (charset, this->mclass));
}

/*====================================================================*
 *
 *   bool istoken (char const *literal) const;
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscanfile::istoken (char const * literal) const 

{
	return (std::strcmp (literal, this->mtoken) == 0);
}

/*====================================================================*
 *
 *   oscanfile & flush ();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::flush () 

{
	this->mcount = 0;
	this->mtoken [0] = (char) (0);
	this->mclass = (char) (0);
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & scanbreak ();
 *
 *   expand the token buffer in fibanacci multiples of mblock, if
 *   full; update cursor position then append the break character
 *   to the token buffer; fetch the next character from the unget
 *   buffer or from stdin if the unget buffer is empty;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::scanbreak () 

{
	if (this->mcount >= this->mlimit) 
	{
		char * otoken = this->mtoken;
		this->mlimit = this->mlimit + this->mblock;
		this->mblock = this->mlimit - this->mblock;
		this->mtoken = new char [this->mlimit + 1];
		for (this->mindex = 0; mindex < this->mcount; this->mindex++) 
		{
			this->mtoken [this->mindex] = otoken [this->mindex];
		}
		delete [] otoken;
	}
	this->count (this->mbreak);
	this->mtoken [this->mcount++] = this->mbreak;
	this->mtoken [this->mcount] = (char) (0);
	if (this->ucount > 0) 
	{
		this->mbreak = this->munget [--this->ucount];
	}
	else
	{
		this->mbreak = std::cin.get ();
	}
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & oscanbreak (unsigned c);
 *
 *   append the break character to the token buffer equals the
 *   character argument;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::scanbreak (unsigned c) 

{
	if (this->isbreak (c)) 
	{
		this->scanbreak ();
	}
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & oscanbreak (char const *charset);
 *
 *   append the break character to the token buffer is present in
 *   charset; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::scanbreak (char const * charset) 

{
	if (this->isbreak (charset)) 
	{
		this->scanbreak ();
	}
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & scanmatch ();
 *
 *   append the break character to the token buffer it is matches the
 *   first token character;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::scanmatch () 

{
	if (this->mbreak == * this->mtoken) 
	{
		this->scanbreak ();
	}
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & scanwhile ();
 *
 *   append break characters to the token buffer while they match
 *   the first token character;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::scanwhile () 

{
	while ((this->mbreak != EOF) && (this->mbreak == * this->mtoken)) 
	{
		this->scanbreak ();
	}
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & scanwhile (unsigned c);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::scanwhile (unsigned c) 

{
	while ((this->mbreak != EOF) && (this->mbreak == (char)(c))) 
	{
		this->scanbreak ();
	}
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & scanwhile (char const *charset);
 *
 *   append break characters to the token buffer while they match
 *   are present in charset; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::scanwhile (char const * charset) 

{
	while ((this->mbreak != EOF) && std::strchr (charset, this->mbreak)) 
	{
		this->scanbreak ();
	}
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & scanspace ();
 *
 *   append break characters to the token buffer while they are
 *   white space charactes; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::scanspace () 

{
	while (oascii::isspace (this->mbreak)) 
	{
		this->scanbreak ();
	}
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & scanalpha ();
 *
 *   append break characters to the token buffer while they are
 *   alphabetic characters;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::scanalpha () 

{
	while (oascii::isalpha (this->mbreak)) 
	{
		this->scanbreak ();
	}
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & scandigit ();
 *
 *   append break characters to the token buffer while they are
 *   decimal digits;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::scandigit () 

{
	while (oascii::isdigit (this->mbreak)) 
	{
		this->scanbreak ();
	}
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & scanalnum ();
 *
 *   append break characters to the token buffer while they are
 *   alphanumeric characters;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::scanalnum () 

{
	while (oascii::isalnum (this->mbreak)) 
	{
		this->scanbreak ();
	}
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & scanuntil ();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::scanuntil () 

{
	while ((this->mbreak != EOF) && (this->mbreak != * this->mtoken)) 
	{
		this->scanbreak ();
	}
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & scanuntil (unsigned c);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::scanuntil (unsigned c) 

{
	while ((this->mbreak != EOF) && (this->mbreak != (char)(c))) 
	{
		this->scanbreak ();
	}
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & scanuntil (char const *charset);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::scanuntil (char const * charset) 

{
	while ((this->mbreak != EOF) && !strchr (charset, this->mbreak)) 
	{
		this->scanbreak ();
	}
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & scanquote (unsigned c);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::scanquote (unsigned c) 

{
	while ((this->mbreak != EOF) && (this->mbreak != (char)(c))) 
	{
		if (this->mbreak == '\\') 
		{
			this->scanbreak ();
		}
		this->scanbreak ();
	}
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & scanquote (char const *charset);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::scanquote (char const * charset) 

{
	while ((this->mbreak != EOF) && strchr (charset, this->mbreak)) 
	{
		if (this->mbreak == '\\') 
		{
			this->scanbreak ();
		}
		this->scanbreak ();
	}
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & scanquote ();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::scanquote () 

{
	while ((this->mbreak != EOF) && (this->mbreak != * this->mtoken)) 
	{
		if (this->mbreak == '\\') 
		{
			this->scanbreak ();
		}
		this->scanbreak ();
	}
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & scangroup (unsigned c);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::scangroup (unsigned c) 

{
	while ((this->mbreak != EOF) && (this->mbreak != (char)(c))) 
	{
		switch (this->mbreak) 
		{
		case '(':
			this->scanbreak ().scangroup (')');
			break;
		case '[':
			this->scanbreak ().scangroup (']');
			break;
		case '{':
			this->scanbreak ().scangroup ('}');
			break;
		case '\"':
			this->scanbreak ().scanquote ('\"');
			break;
		case '\'':
			this->scanbreak ().scanquote ('\'');
			break;
		case '\\':
			this->scanbreak ();
			break;
		default:
			break;
		}
		this->scanbreak ();
	}
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & scangroup (char const *charset);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::scangroup (char const * charset) 

{
	while ((this->mbreak != EOF) && !strchr (charset, this->mbreak)) 
	{
		switch (this->mbreak) 
		{
		case '(':
			this->scanbreak ().scangroup (')');
			break;
		case '[':
			this->scanbreak ().scangroup (']');
			break;
		case '{':
			this->scanbreak ().scangroup ('}');
			break;
		case '\"':
			this->scanbreak ().scanquote ('\"');
			break;
		case '\'':
			this->scanbreak ().scanquote ('\'');
			break;
		case '\\':
			this->scanbreak ();
			break;
		default:
			break;
		}
		this->scanbreak ();
	}
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & scanblock (char const *literal);
 *
 *   scan until an inverted pair is detected; string literal contains
 *   the starting pair, such as "{*", "<?" and so on;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::scanblock (char const * literal) 

{
	while ((this->mbreak != EOF) && (this->mbreak != * literal)) 
	{
		literal++;
		while ((this->mbreak != EOF) && (this->mbreak != * literal)) 
		{
			this->scanbreak ();
		}
		this->scanbreak ();
		literal--;
	}
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & scanblock ();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::scanblock () 

{
	while ((this->mbreak != EOF) && (this->mbreak != * this->mtoken)) 
	{
		this->mtoken++;
		while ((this->mbreak != EOF) && (this->mbreak != * this->mtoken)) 
		{
			this->scanbreak ();
		}
		this->scanbreak ();
		this->mtoken--;
	}
	return (* this);
}

/*====================================================================*
 *
 *   bool havebreak (unsigned c);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscanfile::havebreak (unsigned c) 

{
	if (this->isbreak (c)) 
	{
		this->scanbreak ();
		return (true);
	}
	return (false);
}

/*====================================================================*
 *
 *   bool havebreak (char const *charset);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscanfile::havebreak (char const * charset) 

{
	if (this->isbreak (charset)) 
	{
		this->scanbreak ();
		return (true);
	}
	return (false);
}

/*====================================================================*
 *
 *   oscanfile & scantoken ();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::scantoken () 

{
	if (this->mbreak == EOF) 
	{
		this->flush ();
	}
	else if (oascii::isspace (this->mbreak)) 
	{
		this->mclass = TOKEN_SPACE;
		this->scanspace ();
	}
	else if (oascii::isalpha (this->mbreak)) 
	{
		this->mclass = TOKEN_ALPHA;
		this->scanalnum ();
	}
	else if (oascii::isdigit (this->mbreak)) 
	{
		this->mclass = TOKEN_DIGIT;
		this->scandigit ();
	}
	else
	{
		this->mclass = this->mbreak;
		this->scanbreak ();
	}
	return (* this);
}

/*====================================================================*
 *
 *   bool havetoken (char const *literal);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscanfile::havetoken (char const * literal) 

{
	if (this->istoken (literal)) 
	{
		this->skiptoken ();
		return (true);
	}
	else
	{
		return (false);
	}
}

/*====================================================================*
 *
 *   char * copytoken () const;
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * oscanfile::copytoken () const 

{
	char * string = new char [this->mcount + 1];
	std::strncpy (string, this->mtoken, this->mcount);
	return ((char const *) (string));
}

/*====================================================================*
 *
 *   oscanfile & *copytoken (char buffer[], size_t length);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::copytoken (char buffer [], size_t length) 

{
	std::strncpy (buffer, this->mtoken, length);
	buffer [--length] = (char) (0);
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & skiptoken (char const *literal)
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::skiptoken (char const * literal) 

{
	if (this->istoken (literal)) 
	{
		this->skiptoken ();
	}
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & skiptoken ();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::skiptoken () 

{
	this->scanspace ();
	this->flush ();
	this->scantoken ();
	return (* this);
}

/*====================================================================*
 *
 *   bool haveclass (signed c);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscanfile::haveclass (signed c) 

{
	if (this->isclass (c)) 
	{
		this->skiptoken ();
		return (true);
	}
	return (false);
}

/*====================================================================*
 *
 *   bool haveclass (char const *charset);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscanfile::haveclass (char const * charset) 

{
	if (this->isclass (charset)) 
	{
		this->skiptoken ();
		return (true);
	}
	return (false);
}

/*====================================================================*
 *
 *   oscanfile & trimtoken (char const *charset);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::trimtoken (char const * charset) 

{
	unsigned int first = 0;
	unsigned int final = this->mcount;
	while ((first < final) && strchr (charset, this->mtoken [first + 0])) 
	{
		first++;
	}
	while ((final > first) && strchr (charset, this->mtoken [final - 1])) 
	{
		final--;
	}
	for (this->mcount = 0; first < final; this->mtoken [this->mcount] = (char) (0)) 
	{
		this->mtoken [this->mcount++] = this->mtoken [first++];
	}
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & trimtoken ();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::trimtoken () 

{
	unsigned int first = 0;
	unsigned int final = this->mcount;
	while ((first < final) && oascii::isspace (this->mtoken [first + 0])) 
	{
		first++;
	}
	while ((final > first) && oascii::isspace (this->mtoken [final - 1])) 
	{
		final--;
	}
	for (this->mcount = 0; first < final; this->mtoken [this->mcount] = (char) (0)) 
	{
		this->mtoken [this->mcount++] = this->mtoken [first++];
	}
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & lowercase ();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::lowercase () 

{
	ochrlwr::convert (this->mtoken);
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & uppercase ();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::uppercase () 

{
	ochrupr::convert (this->mtoken);
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & write ();
 *
 *   write the current token span to the standard output stream;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::write () 

{
	std::cout.write (this->mtoken, this->mcount);
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & write (ofstream * stream);
 *
 *   write the current token span to an output file stream;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::write (std::ofstream * stream) 

{
	stream->write (this->mtoken, this->mcount);
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & print ();
 *
 *   print the current token span to the standard output stream;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::print () 

{
	std::cout.write (this->mtoken, this->mcount);
	std::cout.write ("\n", 1);
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & print (ofstream * stream);
 *
 *   print the current token span to an output stream;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::print (std::ofstream * stream) 

{
	stream->write (this->mtoken, this->mcount);
	stream->write ("\n", 1);
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & clear ();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::clear () 

{
	this->mbreak = EOF;
	this->mclass = (char) (0);
	this->mcount = 0;
	this->ucount = 0;
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & unget (char const *string);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::unget (char const * string) 

{
	char const * sp;
	if (strlen (string) > this->ulimit - this->ucount) 
	{
		char * ounbuf = this->munget;
		this->ulimit = this->ucount + std::strlen (string);
		this->munget = new char [this->ulimit + 1];
		for (unsigned int index = 0; index < this->ucount; ++index) 
		{
			this->munget [index] = ounbuf [index];
		}
		delete [] ounbuf;
	}
	for (sp = string; * sp; ++sp);
	while (sp > string) 
	{
		this->munget [this->ucount++] = *--sp;
	}
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile & unget (char c);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile & oscanfile::unget (char c) 

{
	if (this->ucount < this->ulimit) 
	{
		this->munget [this->ucount++] = (char) (c);
	}
	return (* this);
}

/*====================================================================*
 *
 *   oscanfile ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile::oscanfile () 

{
	this->mbreak = std::cin.get ();
	this->mclass = (char) (0);
	this->mtoken = new char [_MAXTOKEN + 1];
	this->mtoken [0] = (char) (0);
	this->mblock = _MAXTOKEN;
	this->mlimit = _MAXTOKEN;
	this->mcount = 0;
	this->munget = new char [_MAXUNGET + 1];
	this->munget [0] = (char) (0);
	this->ulimit = _MAXUNGET;
	this->ucount = 0;
	return;
};

/*====================================================================*
 *
 *   ~oscanfile ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscanfile::~oscanfile () 

{
	delete [] mtoken;
	delete [] munget;
	return;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

