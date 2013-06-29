/*====================================================================*
 *
 *   oindent.cpp - implementation of the oindent class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oINDENT_SOURCE
#define oINDENT_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstring>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oindent.hpp"

/*====================================================================*
 *
 *   oindent & margin (char const *string);
 *
 *   set the margin string; the margin string is output at the start 
 *   of each line before the repeating indent string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

oindent & oindent::margin (char const * string) 

{
	if (std::strcmp (string, this->mmargin)) 
	{
		delete [] mmargin;
		this->mmargin = new char [strlen (string) +1];
		std::strcpy (this->mmargin, string);
	}
	return (* this);
}

/*====================================================================*
 *
 *   char const * margin (void) const;
 *
 *   get the margin string; the margin string is output at the start 
 *   of each line before the repeating indent string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

char const * oindent::margin (void) const 

{
	return ((char const *) (this->mmargin));
}

/*====================================================================*
 *
 *   oindent & indent (char const *string);
 *
 *   set the indent string; the indent string may be output at the
 *   start of each line after the margin string; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

oindent & oindent::indent (char const * string) 

{
	if (std::strcmp (string, this->mindent)) 
	{
		delete [] mindent;
		this->mindent = new char [strlen (string) +1];
		std::strcpy (this->mindent, string);
	}
	return (* this);
}

/*====================================================================*
 *
 *   char const * indent (void) const;
 *
 *   get the indent string; the indent string may be output at the
 *   start of each line after the margin string; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

char const * oindent::indent (void) const 

{
	return ((char const *) (this->mindent));
}

/*====================================================================*
 *
 *   oindent & finish (char const *string);
 *
 *   set the finish string; the finish string is output at the end 
 *   of each line before the repeating record string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

oindent & oindent::finish (char const * string) 

{
	if (std::strcmp (string, this->mfinish)) 
	{
		delete [] mfinish;
		this->mfinish = new char [strlen (string) +1];
		std::strcpy (this->mfinish, string);
	}
	return (* this);
}

/*====================================================================*
 *
 *   char const * finish (void) const;
 *
 *   get the finish string; the finish string is output at the end 
 *   of each line before the repeating record string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

char const * oindent::finish (void) const 

{
	return ((char const *) (this->mfinish));
}

/*====================================================================*
 *
 *   oindent & record (char const *string);
 *
 *   set the record string; the record string may be output at the
 *   end of each line after the finish string; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

oindent & oindent::record (char const * string) 

{
	if (std::strcmp (string, this->mrecord)) 
	{
		delete [] mrecord;
		this->mrecord = new char [strlen (string) +1];
		std::strcpy (this->mrecord, string);
	}
	return (* this);
}

/*====================================================================*
 *
 *   char const * record (void) const;
 *
 *   get the record string; the record string may be output at the
 *   end of each line after the finish string; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

char const * oindent::record (void) const 

{
	return ((char const *) (this->mrecord));
}

/*====================================================================*
 *   
 *   oindent & level (signed level);
 *
 *   output the margin string followed by count indent strings;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

oindent & oindent::level (void) 

{
	oindent::print (this->mmargin, this->mindent, this->mlevel);
	return (* this);
}

oindent & oindent::level (signed level) 

{
	this->mlevel = level;
	oindent::print (this->mmargin, this->mindent, this->mlevel);
	return (* this);
}

/*====================================================================*
 *   
 *   oindent & space (signed space);
 *   
 *   output the finish string followed by count record strings;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

oindent & oindent::space (void) 

{
	oindent::print (this->mfinish, this->mrecord, this->mspace);
	return (* this);
}

oindent & oindent::space (signed space) 

{
	this->mspace = space;
	oindent::print (this->mfinish, this->mrecord, this->mspace);
	return (* this);
}

/*====================================================================*
 *   
 *   oindent & newline (char const *margin, char const *indent, signed level)
 *   
 *   output the margin string followed by count indent strings;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

void oindent::newline (char const * margin, char const * indent, signed level) 

{
	oindent::print (margin, indent, level);
	return;
}

/*====================================================================*
 *   
 *   oindent & std::endline (char const *finish, char const *record, signed space);
 *   
 *   output the finish string followed by count record strings;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

void oindent::endline (char const * finish, char const * record, signed space) 

{
	oindent::print (finish, record, space);
	return;
}

/*====================================================================*
 *
 *   oindent & print (signed level, signed space, char const *string);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

oindent & oindent::print (signed level, signed space, char const * string) 

{
	oindent::print (this->mmargin, this->mindent, level);
	std::cout << string;
	oindent::print (this->mfinish, this->mrecord, space);
	return (* this);
}

/*====================================================================*
 *   
 *   void print (char const *prefix, char const *suffix, signed count);
 *
 *   print a prefix string followed by count suffix strings; this is
 *   the lowest level indent method;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

void oindent::print (char const * prefix, char const * suffix, signed count) 

{
	for (std::cout << prefix; count-- > 0; std::cout << suffix);
	return;
}

/*====================================================================*
 *
 *   oindent (void) 
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

oindent::oindent (void) 

{
	this->mlevel = 0;
	this->mspace = 1;
	this->mmargin = new char [1];
	this->mmargin [0] = '\0';
	this->mindent = new char [2];
	this->mindent [0] = '\t';
	this->mindent [1] = '\0';
	this->mfinish = new char [1];
	this->mfinish [0] = '\0';
	this->mrecord = new char [2];
	this->mrecord [0] = '\n';
	this->mrecord [1] = '\0';
	return;
}

/*====================================================================*
 *
 *   oindent (void) 
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

oindent::~oindent (void) 

{
	delete [] this->mmargin;
	delete [] this->mindent;
	delete [] this->mfinish;
	delete [] this->mrecord;
	return;
}

/*====================================================================*
 *   end implementation
 *--------------------------------------------------------------------*/

#endif

