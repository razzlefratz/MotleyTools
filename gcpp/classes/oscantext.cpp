/*====================================================================*
 *
 *   oscantext.cpp - implementation of the oscantext class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oSCANTEXT_SOURCE
#define oSCANTEXT_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstring>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/tools.h"
#include "../classes/oscantext.hpp"

/*====================================================================*
 *
 *   bool end () const;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscantext::end () const 

{
	return (this->mstart >= this->mlimit);
}


/*====================================================================*
 *
 *   oscantext & copy (char const * string);
 *
 *   copy string into the input buffer; reset pointer, counters and objects;
 *  
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::operator= (char const * string) 

{
	this->copy (string);
	return (* this);
}


oscantext & oscantext::copy (char const * string) 

{
	off_t length = std::strlen (string);
	this->reset (length);
	std::strcpy (this->mstart, string);
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & read (char const *filename);
 * 
 *   read an entire input stream into the input buffer; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::read (char const * filename) 

{
	if ((filename) && (* filename)) 
	{
		std::ifstream stream;
		stream.open (filename, std::ios::binary);
		if (stream.good ()) 
		{
			this->read (&stream);
		}
		stream.close ();
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & read (ifstream * stream);
 *
 *   read an entire input stream into the input buffer; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::read (std::ifstream * stream) 

{
	stream->seekg (0, std::ios::end);
	off_t length = stream->tellg ();
	stream->seekg (0, std::ios::beg);
	this->reset (length);
	stream->read (this->mstart, length);
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & read ();
 *
 *   read the standard input stream into the input buffer; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::read () 

{
	std::cin.seekg (0, std::ios::end);
	off_t length = std::cin.tellg ();
	std::cin.seekg (0, std::ios::beg);
	this->reset (length);
	std::cin.read (this->mstart, length);
	return (* this);
}


/*====================================================================*
 *
 *   bool isempty () const;
 *
 *   return true if the input buffer is exhausted; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscantext::isempty () const 

{
	return (this->mstart >= this->mlimit);
}


/*====================================================================*
 *
 *   char character () const;
 *
 *   return the break character value;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char oscantext::character () const 

{
	return (* this->mbreak);
}


/*====================================================================*
 *
 *   bool istoken (char const *literal) const;
 *
 *   return true if the token string matches the literal string argument;
 *   this function is essentially strncmp () coded inline for speed;
 * 
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscantext::istoken (char const * literal) const 

{
	char const * pointer = this->mstart;
	while ((pointer < this->mbreak) && (* pointer == * literal)) 
	{
		pointer++;
		literal++;
	}
	return (* literal == (char) (0));
}


/*====================================================================*
 *
 *   size_t tokensize () const;
 *
 *   return the length of the current token; the length is the difference
 *   between the break pointer and the start pointer;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

size_t oscantext::tokensize () const 

{
	return (this->mbreak - this->mstart);
}


/*====================================================================*
 *
 *   char const * tokentext ();
 *
 *   copy the current token span to an internal token buffer and
 *   return the buffer address; enlarge the buffer to accomodate
 *   longer tokens, as needed; this speeds access to the current
 *   token because the internal token buffer is reused, avoiding
 *   the overhead of repeated reallocation; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * oscantext::tokentext () 

{
	if (this->mbreak > this->mstart + this->mwidth) 
	{
		delete [] this->mtoken;
		this->mwidth = this->mbreak - this->mstart;
		this->mtoken = new char [this->mwidth + 1];
		this->mtoken [0] = (char) (0);
	}
	this->readtoken (this->mtoken, this->mwidth);
	return ((char const *) (this->mtoken));
}


/*====================================================================*
 *
 *   char const * savetoken ();
 *
 *   make a copy of the current token span; return the copy address;
 *   the caller is responsible for deleting the copy;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * oscantext::savetoken () 

{
	this->mindex = new char [this->mbreak - this->mstart + 1];
	this->readtoken (this->mindex, this->mbreak - this->mstart + 1);
	return ((char const *) (this->mindex));
}


/*====================================================================*
 *
 *   oscantext & readtoken (char buffer[], size_t length);
 *
 *   copy the current token into a user supplied buffer and return 
 *   the object address; truncate the token, if needed;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::readtoken (char buffer [], size_t length) 

{
	if ((buffer) && (length--)) 
	{
		this->mindex = this->mstart;
		while ((this->mindex < this->mbreak) && (length--)) 
		{
			* buffer++ = * this->mindex++;
		}
		* buffer = (char) (0);
	}
	return (* this);
}


/*====================================================================*
 *
 *   bool isspace () const;
 *
 *   return true of the break character is white space;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscantext::isspace () const 

{
	return (oascii::isspace (* this->mbreak));
}


/*====================================================================*
 *
 *   bool isalpha () const;
 *
 *   return true if the break character is alphabetic;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscantext::isalpha () const 

{
	return (oascii::isalpha (* this->mbreak));
}


/*====================================================================*
 *
 *  bool isdigit () const;
 *
 *   return true if the break character is numeric;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscantext::isdigit () const 

{
	return (oascii::isdigit (* this->mbreak));
}


/*====================================================================*
 *
 *  bool isalnum () const;
 *
 *   return true if the break character is alphanumeric;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscantext::isalnum () const 

{
	return (oascii::isalnum (* this->mbreak));
}


/*====================================================================*
 *
 *   bool isident () const;
 *
 *   return true if the token is an identifier ("[A-Za-z0-9$_]");             
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscantext::isident () const 

{
	return (oascii::isident (* this->mbreak));
}


/*====================================================================*
 *
 *  bool ispunct () const;
 *
 *   return true if the break character is punctuation;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscantext::ispunct () const 

{
	return (oascii::ispunct (* this->mbreak));
}


/*====================================================================*
 *
 *  bool isarith () const;
 *
 *   return true if the break character is punctuation;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscantext::isarith () const 

{
	return (oascii::isarith (* this->mbreak));
}


/*====================================================================*
 *
 *  bool islogic () const;
 *
 *   return true if the break character is punctuation;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscantext::islogic () const 

{
	return (oascii::islogic (* this->mbreak));
}


/*====================================================================*
 *
 *  bool isgroup () const;
 *
 *   return true if the break character is group punctuation;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscantext::isgroup () const 

{
	return (oascii::isgroup (* this->mbreak));
}


/*====================================================================*
 *
 *   bool isclass (unsigned c) const;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscantext::isclass (unsigned c) const 

{
	return (this->mclass == (char) (c));
}


/*====================================================================*
 *
 *   bool isclass (char const * charset) const;
 *
 *   return true if the class character is a member of the character set
 *   string argument; this function is essentially strchr () coded inline
 *   for speed; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscantext::isclass (char const * charset) const 

{
	while ((* charset) && (* charset != this->mclass)) 
	{
		charset++;
	}
	return (* charset != (char) (0));
}


/*====================================================================*
 *
 *   oscantext & flush ();
 *
 *   flush the current token string by advancing the start pointer 
 *   to the break pointer and counting characters as we go; 
 *
 *   clear the token string and the class character in preparation 
 *   for the next scan;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::flush () 

{
	while (this->mstart < this->mbreak) 
	{
		this->count (* this->mstart++);
	}
	this->mtoken [0] = (char) (0);
	this->mclass = (char) (0);
	return (* this);
}


/*====================================================================*
 *
 *   oscantext &scanmatch ();
 *
 *   collect the break character if it matches the first token
 *   character;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::scanmatch () 

{
	if (this->ismatch ()) 
	{
		this->mbreak++;
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantext &scanbreak ();
 *
 *   collect the break character unless the input is exhausted; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::scanbreak () 

{
	if (this->mbreak < this->mlimit) 
	{
		this->mbreak++;
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantext &scanbreak (unsigned c);
 *
 *   collect the break character if it is in charset;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::scanbreak (unsigned c) 

{
	if (this->isbreak (c)) 
	{
		this->mbreak++;
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantext &scanbreak (char const * charset);
 *
 *   collect the break character if it is in charset;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::scanbreak (char const * charset) 

{
	if (this->isbreak (charset)) 
	{
		this->mbreak++;
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantest & scanblank ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::scanblank () 

{
	while ((this->mbreak < this->mlimit) && oascii::isblank (* this->mbreak)) 
	{
		this->mbreak++;
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantest & scanspace ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::scanspace () 

{
	while ((this->mbreak < this->mlimit) && oascii::isspace (* this->mbreak)) 
	{
		this->mbreak++;
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & scanalpha ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::scanalpha () 

{
	while ((this->mbreak < this->mlimit) && oascii::isalpha (* this->mbreak)) 
	{
		this->mbreak++;
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & scandigit ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::scandigit () 

{
	while ((this->mbreak < this->mlimit) && oascii::isdigit (* this->mbreak)) 
	{
		this->mbreak++;
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & scanalnum ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::scanalnum () 

{
	while ((this->mbreak < this->mlimit) && oascii::isalnum (* this->mbreak)) 
	{
		this->mbreak++;
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & scanident ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::scanident () 

{
	while ((this->mbreak < this->mlimit) && oascii::isident (* this->mbreak)) 
	{
		this->mbreak++;
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & scanwhile ();
 *
 *   collect characters that match the token start character; return 
 *   the object address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::scanwhile () 

{
	while ((this->mbreak < this->mlimit) && (* this->mbreak == * this->mstart)) 
	{
		this->mbreak++;
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & scanwhile (unsigned c);
 *
 *   collect characters that match character c; return the object
 *   address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::scanwhile (unsigned c) 

{
	while ((this->mbreak < this->mlimit) && (* this->mbreak == (char) (c))) 
	{
		this->mbreak++;
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & scanwhile (char const * charset);
 *
 *   collect character that are in charset; return the object address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::scanwhile (char const * charset) 

{
	while ((this->mbreak < this->mlimit) && this->isbreak (charset)) 
	{
		this->mbreak++;
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & scanwhile (bool type (unsigned c));
 *
 *   collect character that are in charset; return the object address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::scanwhile (bool type (unsigned c)) 

{
	while ((this->mbreak < this->mlimit) && type (* this->mbreak)) 
	{
		this->mbreak++;
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & scanuntil ();
 *
 *   collect characters that do not match the token start character;
 *   return the object address;
 *
 *   this method can be used to collect literal strings enclosed in quotes
 *   or other characters;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::scanuntil () 

{
	while ((this->mbreak < this->mlimit) && (* this->mbreak != * this->mstart)) 
	{
		this->mbreak++;
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & scanuntil (unsigned c);
 *
 *   collect characters that do not match character c; return the 
 *   object address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::scanuntil (unsigned c) 

{
	while ((this->mbreak < this->mlimit) && (* this->mbreak != (char) (c))) 
	{
		this->mbreak++;
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & scanuntil (char const * charset);
 *
 *   collect characters that are not in charset; return the object
 *   address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::scanuntil (char const * charset) 

{
	while ((this->mbreak < this->mlimit) && !this->isbreak (charset)) 
	{
		this->mbreak++;
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & scanuntil (bool type (unsigned c));
 *
 *   collect character that are in charset; return the object address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::scanuntil (bool type (unsigned c)) 

{
	while ((this->mbreak < this->mlimit) && !type (* this->mbreak)) 
	{
		this->mbreak++;
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & scanquote ();
 *
 *   collect characters that do not match the token start character
 *   and escaped characters that do; return the object address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::scanquote () 

{
	while ((this->mbreak < this->mlimit) && (* this->mbreak != * this->mstart)) 
	{
		if (* this->mbreak++ == '\\') 
		{
			this->scanbreak ();
		}
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & scanquote (unsigned c);
 *
 *   collect characters that do not match character c and escaped 
 *   characters that do; return the object address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::scanquote (unsigned c) 

{
	while ((this->mbreak < this->mlimit) && (* this->mbreak != (char) (c))) 
	{
		if (* this->mbreak++ == '\\') 
		{
			this->scanbreak ();
		}
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & scanquote (char const * charset);
 *
 *   collect characters that are not in charset and escaped 
 *   escaped characters that are; return the object address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::scanquote (char const * charset) 

{
	while ((this->mbreak < this->mlimit) && !this->isbreak (charset)) 
	{
		if (* this->mbreak++ == '\\') 
		{
			this->scanbreak ();
		}
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & scanblock ();
 *
 *   scan characters until an inverted pair is detected; the pair
 *   must oppose (occur in the opposite order as) the first two 
 *   token characters;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::scanblock () 

{
	while ((this->mbreak < this->mlimit) && (* this->mbreak != * this->mstart)) 
	{
		this->mstart++;
		this->scanuntil ();
		this->scanmatch ();
		this->mstart--;
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & scanblock (char const *literal)
 *
 *   scan characters until an inverted pair is detected; the pair
 *   must occur in the same order as the first two literal characters;
 *
 *   this method collects text between inverted delimiter pairs like:
 *   
 *   "{* ... *}" or "-- ... --"
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::scanblock (char const * literal) 

{
	while ((this->mbreak < this->mlimit) && (* this->mbreak != literal [1])) 
	{
		this->scanuntil (literal [0]);
		this->scanbreak (literal [0]);
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & scangroup (unsigned c);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::scangroup (unsigned c) 

{
	while ((this->mbreak < this->mlimit) && (* this->mbreak != (char) (c))) 
	{
		switch (* this->mbreak++) 
		{
		case '(':
			this->scangroup (')');
			this->scanbreak (')');
			break;
		case '[':
			this->scangroup (']');
			this->scanbreak (']');
			break;
		case '{':
			this->scangroup ('}');
			this->scanbreak ('}');
			break;
		case '\"':
			this->scanquote ('\"');
			this->scanbreak ('\"');
			break;
		case '\'':
			this->scanquote ('\'');
			this->scanbreak ('\'');
			break;
		default:
			break;
		}
	}
	return (* this);
}


/*====================================================================*
 *   
 *   oscantext &oscantext::scantoken ();
 *
 *   collect the next space, alphanumeric or numeric token from the input
 *   buffer and set the class character; return the object address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::scantoken () 

{
	if (oscantext::isempty ()) 
	{
		this->mclass = (char) (0);
	}
	else if (oscantext::isspace ()) 
	{
		this->mclass = TOKEN_SPACE;
		this->scanspace ();
	}
	else if (oscantext::isalpha ()) 
	{
		this->mclass = TOKEN_ALPHA;
		this->scanalpha ();
	}
	else if (oscantext::isdigit ()) 
	{
		this->mclass = TOKEN_DIGIT;
		this->scandigit ();
	}
	else 
	{
		this->mclass = * this->mbreak++;
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & elaborate ();
 *
 *   print token classes and strings on stdout;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::elaborate () 

{
	while (!this->isempty ()) 
	{
		switch (this->nexttoken ().tokentype ()) 
		{
		case TOKEN_SPACE:
			std::cout << "[SPACE[" << this->tokentext () << "]]" << std::endl;
			break;
		case TOKEN_ALPHA:
			std::cout << "[ALPHA[" << this->tokentext () << "]]" << std::endl;
			break;
		case TOKEN_DIGIT:
			std::cout << "[DIGIT[" << this->tokentext () << "]]" << std::endl;
			break;
		default:
			std::cout << "[PUNCT[" << this->tokentext () << "]]" << std::endl;
			break;
		}
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & translate (char const * oldtoken, char const * newtoken);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::translate (char const * oldtoken, char const * newtoken) 

{
	if (this->istoken (oldtoken)) 
	{
		std::cout.write (newtoken, std::strlen (newtoken));
		return (* this);
	}
	this->write ();
	return (* this);
}


/*====================================================================*
 *
 *   bool ismatch () const;
 *
 *   return true if the current character matches the first token
 *   character; this provides a generic means of detecting literal  
 *   string terminators, double-character sequences and so on; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscantext::ismatch () const 

{
	return ((this->mstart < this->mlimit) && (* this->mbreak == * this->mstart));
}


/*====================================================================*
 *
 *   bool isbreak (unsigned c) const;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscantext::isbreak (unsigned c) const 

{
	return ((this->mstart < this->mlimit) && (* this->mbreak == (char) (c)));
}


/*====================================================================*
 *
 *   bool isbreak (char const * charset) const;
 *
 *   return true if the break character is in charset; 
 *
 *   this function is essentially strchr () coded inline for speed; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscantext::isbreak (char const * charset) const 

{
	while ((* charset) && (* this->mbreak != * charset)) 
	{
		charset++;
	}
	return (* charset != (char) (0));
}


/*====================================================================*
 *
 *   bool isbreak (bool type (unsigned)) const;
 *
 *   return true if the current character is of the specifed type;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscantext::isbreak (bool (* type) (unsigned)) const 

{
	return ((this->mstart < this->mlimit) && type (* this->mbreak));
}


/*====================================================================*
 *
 *   bool havematch ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscantext::havematch () 

{
	if (this->ismatch ()) 
	{
		this->scanbreak ();
		return (true);
	}
	return (false);
}


/*====================================================================*
 *
 *   bool havebreak (unsigned c);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscantext::havebreak (unsigned c) 

{
	while (this->isbreak (c)) 
	{
		this->scanbreak ();
		return (true);
	}
	return (false);
}


/*====================================================================*
 *
 *   bool havebreak (char const * charset);
 *
 *   keep the current character if is is a member of the character 
 *   set string argument and return true; otherwise, do nothing and 
 *   return false; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscantext::havebreak (char const * charset) 

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
 *   bool havebreak (bool type (unsigned));
 *
 *   keep the current character if it is of the specified type and
 *   return true; otherwise, do nothing and return false; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscantext::havebreak (bool type (unsigned)) 

{
	if (this->isbreak (type)) 
	{
		this->scanbreak ();
		return (true);
	}
	return (false);
}


/*====================================================================*
 *
 *   char class () const;
 *
 *   return the class character value;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char oscantext::tokentype () const 

{
	return (this->mclass);
}


/*====================================================================*
 *
 *   oscantext & class (char c);
 *
 *   set the class character value; the scantoken method resets this 
 *   character but an application can change it to anything it likes; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::tokentype (char c) 

{
	this->mclass = (char) (c);
	return (* this);
}


/*====================================================================*
 *
 *   bool haveclass (unsigned c);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscantext::haveclass (unsigned c) 

{
	if (this->isclass (c)) 
	{
		this->nexttoken ();
		return (true);
	}
	return (false);
}


/*====================================================================*
 *
 *   bool haveclass (char const * charset);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscantext::haveclass (char const * charset) 

{
	if (this->isclass (charset)) 
	{
		this->nexttoken ();
		return (true);
	}
	return (false);
}


/*====================================================================*
 *
 *   bool havetoken (char const *literal);
 *
 *   compare the literal string argument to the current token string; if
 *   they match then collect the next non-blank token and return logical
 *   true; otherwise; do nothing and return logical false;
 *
 *   this method lets applications test for special tokens and act on
 *   them; if the token was present then the following token is ready
 *   for inspection;
 *
 *   if (scanner.havetoken ("public"))
 *   {
 *           if (scanner.havetoken ("function"))
 *      else if (scanner.havetoken ("subroutine"))
 *      else ...
 *   }
 *   else if (scanner.have token ("private"))
 *   {
 *   }
 *   else ... 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oscantext::havetoken (char const * literal) 

{
	if (this->istoken (literal)) 
	{
		this->nexttoken ();
		return (true);
	}
	return (false);
}


/*====================================================================*
 *
 *   oscantext & nexttoken ();
 *
 *   unconditionally collect the next non-blank token; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::nexttoken () 

{
	this->scanspace ();
	this->flush ();
	this->scantoken ();
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & cleanse ();
 *
 *   normalize the input buffer by replacing control characters with
 *   ascii spaces; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::cleanse () 

{
	for (this->mindex = this->mstart; this->mindex < this->mlimit; this->mindex++) 
	{
		if (oascii::isprint (* this->mindex)) 
		{
			continue;
		}
		if (oascii::isspace (* this->mindex)) 
		{
			continue;
		}
		* this->mindex = 0x20;
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & trimtoken ();
 *
 *   move start and break pointers to discard leading and trailing
 *   space from the token string before inspecting or retrieving a 
 *   token;
 *
 *   char *string = scanner.scanuntil (";").trim ().toketext ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::trimtoken () 

{
	while ((this->mstart < this->mbreak) && oascii::isspace (* this->mstart)) 
	{
		this->count (* this->mstart);
		this->mstart++;
	}
	while ((this->mstart < this->mbreak) && oascii::isspace (* (this->mbreak - 1))) 
	{
		this->mbreak--;
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & trimtoken (char const * charset);
 *
 *   move start and break pointers to discard leading and trailing
 *   spaces and puncutation from the token string before inspecting
 *   or retrieving it; only characters in charset are removed;
 *
 *   char *string = scanner.scanuntil (";").trimtoken ().tokentext ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::trimtoken (char const * charset) 

{
	while ((this->mstart < this->mbreak) && !std::strchr (charset, * this->mstart)) 
	{
		this->count (* this->mstart++);
	}
	while ((this->mbreak > this->mstart) && !std::strchr (charset, * (this->mbreak - 1))) 
	{
		this->mbreak--;
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantext &uppercase ();
 *
 *   convert token string to lower case; this method may be called 
 *   either before or after retrieving token text;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::uppercase () 

{
	ochrupr::convert (this->mtoken);
	return (* this);
}


/*====================================================================*
 *
 *   oscantext &lowercase ();
 *
 *   convert token string to lower case; this method may be called 
 *   either before or after retrieving token text;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::lowercase () 

{
	ochrlwr::convert (this->mtoken);
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & write ();
 *
 *   write the current token span to the standard output stream;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::write () 

{
	std::cout.write (this->mstart, this->mbreak - this->mstart);
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & write (ofstream * stream);
 *
 *   write the current token span to an output file stream;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::write (std::ofstream * stream) 

{
	stream->write (this->mstart, this->mbreak - this->mstart);
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & print ();
 *
 *   print the current token span to the standard output stream;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::print () 

{
	std::cout.write (this->mstart, this->mbreak - this->mstart);
	std::cout.write ("\n", 1);
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & print (ofstream *stream);
 *
 *   print the current token span to an output stream;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::print (std::ofstream * stream) 

{
	stream->write (this->mstart, this->mbreak - this->mstart);
	stream->write ("\n", 1);
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & unget ();
 *
 *   return the current token to the input buffer, allowing rescan 
 *   if the current scan is unsatisfactory;
 *
 *   clear the token string and the class character in preparation 
 *   for the next scan;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::unget () 

{
	this->mbreak = this->mstart;
	this->mtoken [0] = (char) (0);
	this->mclass = (char) (0);
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & unget (char c);
 *
 *   return one character to the input buffer, making it the current
 *   character;
 *
 *   clear the token string and the class character in preparation 
 *   for the next scan;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::unget (char c) 

{
	if (this->mbreak > this->minput) 
	{
		*--this->mbreak = (char) (c);
	}
	this->mstart = this->mbreak;
	this->mtoken [0] = (char) (0);
	this->mclass = (char) (0);
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & unget (char const *string);
 *
 *   return a string to the imput buffer, causing it to be scanned
 *   next;
 *
 *   clear the token string and the class character in preparation 
 *   for the next scan;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::unget (char const * string) 

{
	char const * sp;
	for (sp = string; * sp; ++sp);
	while ((this->mbreak > this->minput) && (sp > string)) 
	{
		*--this->mbreak = *--sp;
	}
	this->mstart = this->mbreak;
	this->mtoken [0] = (char) (0);
	this->mclass = (char) (0);
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & scangroup (char const * charset);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::scangroup (char const * charset) 

{
	while ((this->mbreak < this->mlimit) && !this->isbreak (charset)) 
	{
		switch (* this->mbreak++) 
		{
		case '(':
			this->scangroup (")");
			this->scanbreak (")");
			break;
		case '[':
			this->scangroup ("]");
			this->scanbreak ("]");
			break;
		case '{':
			this->scangroup ("}");
			this->scanbreak ("}");
			break;
		case '\"':
			this->scanquote ("\"");
			this->scanbreak ("\"");
			break;
		case '\'':
			this->scanquote ("\'");
			this->scanbreak ("\'");
			break;
		default:
			break;
		}
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & enumerate ();
 *
 *   print token strings on stdout, one per line, as they are parsed;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::enumerate () 

{
	while (!this->isempty ()) 
	{
		this->nexttoken ().print ();
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & reset ();
 *
 *   delete input and token buffers and allocate new ones according 
 *   to length; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::reset (off_t length) 

{
	delete [] this->minput;
	this->minput = new char [this->munget + length + 1];
	this->mstart = this->minput + this->munget;
	this->mlimit = this->mstart + length;
	this->mbreak = this->mstart;
	this->mstart [0] = (char) (0);
	this->mlimit [0] = (char) (0);
	delete [] this->mtoken;
	this->mtoken = new char [this->mwidth + 1];
	this->mtoken [0] = (char) (0);
	this->mclass = (char) (0);
	return (* this);
}


/*====================================================================*
 *
 *   oscantext & clear ();
 *
 *   erase the input buffer; reset counters, pointers and objects;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext & oscantext::clear () 

{
	this->reset ((off_t) (0));
	return (* this);
}


/*====================================================================*
 *
 *   oscantext ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext::oscantext () 

{
	this->munget = oSCANTEXT_UNGET_LENGTH;
	this->minput = new char [this->munget + 1];
	this->mstart = this->minput + this->munget;
	this->mlimit = this->mstart;
	this->mbreak = this->mstart;
	this->mwidth = oSCANTEXT_TOKEN_LENGTH;
	this->mtoken = new char [this->mwidth + 1];
	this->mtoken [0] = (char) (0);
	this->mclass = (char) (0);
	this->reset ((off_t) (0));
	return;
}


/*====================================================================*
 *
 *   oscantext (ifstream * stream);
 * 
 *   open the named file and read contents into the input buffer;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext::oscantext (std::ifstream * stream) 

{
	this->munget = oSCANTEXT_UNGET_LENGTH;
	this->minput = new char [this->munget + 1];
	this->mstart = this->minput + this->munget;
	this->mlimit = this->mstart;
	this->mbreak = this->mstart;
	this->mwidth = oSCANTEXT_TOKEN_LENGTH;
	this->mtoken = new char [this->mwidth + 1];
	this->mtoken [0] = (char) (0);
	this->mclass = (char) (0);
	this->read (stream);
	return;
}


/*====================================================================*
 *
 *   oscantext (char const *string);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext::oscantext (char const * string) 

{
	this->munget = oSCANTEXT_UNGET_LENGTH;
	this->minput = new char [this->munget + 1];
	this->mstart = this->minput + this->munget;
	this->mlimit = this->mstart;
	this->mbreak = this->mstart;
	this->mwidth = oSCANTEXT_TOKEN_LENGTH;
	this->mtoken = new char [this->mwidth + 1];
	this->mtoken [0] = (char) (0);
	this->mclass = (char) (0);
	this->copy (string);
	return;
}


/*====================================================================*
 *
 *   ~oscantext ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscantext::~oscantext () 

{
	delete [] this->mtoken;
	delete [] this->minput;
	return;
}


/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

