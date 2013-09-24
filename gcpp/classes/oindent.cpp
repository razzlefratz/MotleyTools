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
 *   oindent & space (signed space);
 *   
 *   set the line spacing; the line spacing determines how many times
 *   the record string is printed at the end of each line; 
 *   
 *--------------------------------------------------------------------*/

oindent & oindent::space (signed space)

{
	this->mspace = space;
	return (* this);
}

/*====================================================================*
 *   
 *   signed space (signed space) const;
 *   
 *   set the line spacing; the line spacing determines how many times
 *   the record string is printed at the end of each line; 
 *   
 *--------------------------------------------------------------------*/

signed oindent::space (void) const

{
	return (this->mspace);
}

/*====================================================================*
 *   
 *   oindent & level (signed level);
 *
 *   set the indent level; the indent level determines the number of
 *   time the indent string is printed at the start of each new line;
 *   
 *--------------------------------------------------------------------*/

oindent & oindent::level (signed level)

{
	this->mlevel = level;
	return (* this);
}

/*====================================================================*
 *   
 *   signed level (signed level) const;
 *
 *   get the indent level; the indent level determines the number of
 *   time the indent string is printed at the start of each new line;
 *   
 *--------------------------------------------------------------------*/

signed oindent::level (void) const

{
	return (this->mlevel);
}

/*====================================================================*
 *   
 *   oindent & increment ();
 *
 *--------------------------------------------------------------------*/

oindent & oindent::increment ()

{
	this->mlevel++;
	return (* this);
}

/*====================================================================*
 *   
 *   oindent & decrement ();
 *
 *--------------------------------------------------------------------*/

oindent & oindent::decrement ()

{
	if (this->mlevel)
	{
		this->mlevel--;
	}
	return (* this);
}

/*====================================================================*
 *
 *   oindent & margin (char const *string);
 *
 *   set the margin string; the margin string is output at the start 
 *   of each line before the repeating indent string;
 *
 *--------------------------------------------------------------------*/

oindent & oindent::margin (char const * string)

{
	if (std::strcmp (string, this->mmargin))
	{
		delete [] mmargin;
		this->mmargin = new char [strlen (string) +  1];
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
 *--------------------------------------------------------------------*/

char const * oindent::margin (void) const

{
	return ((char const *) (this->mmargin));
}

/*====================================================================*
 *
 *   oindent & offset (char const * string);
 *
 *   set the indent string; the indent string may be output at the
 *   start of each line after the margin string; 
 *
 *--------------------------------------------------------------------*/

oindent & oindent::offset (char const * string)

{
	if (std::strcmp (string, this->moffset))
	{
		delete [] moffset;
		this->moffset = new char [strlen (string) +  1];
		std::strcpy (this->moffset, string);
	}
	return (* this);
}

/*====================================================================*
 *
 *   char const * offset (void) const;
 *
 *   get the indent string; the indent string may be output at the
 *   start of each line after the margin string; 
 *
 *--------------------------------------------------------------------*/

char const * oindent::offset (void) const

{
	return ((char const *) (this->moffset));
}

/*====================================================================*
 *
 *   oindent & finish (char const *string);
 *
 *   set the finish string; the finish string is output at the end 
 *   of each line before the repeating record string;
 *
 *--------------------------------------------------------------------*/

oindent & oindent::finish (char const * string)

{
	if (std::strcmp (string, this->mfinish))
	{
		delete [] mfinish;
		this->mfinish = new char [strlen (string) +  1];
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
 *--------------------------------------------------------------------*/

oindent & oindent::record (char const * string)

{
	if (std::strcmp (string, this->mrecord))
	{
		delete [] mrecord;
		this->mrecord = new char [strlen (string) +  1];
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
 *--------------------------------------------------------------------*/

char const * oindent::record (void) const

{
	return ((char const *) (this->mrecord));
}

/*====================================================================*
 *   
 *   oindent & endline (void) 
 *   oindent & endline (signed space) 
 *   oindent & endline (char const * finish, char const * record, signed space);
 *   
 *   output the finish string followed by count record strings;
 *   
 *--------------------------------------------------------------------*/

oindent & oindent::endline (void)

{
	oindent::print (this->mfinish, this->mrecord, this->mspace);
	return (* this);
}

oindent & oindent::endline (signed space)

{
	oindent::print (this->mfinish, this->mrecord, space);
	return (* this);
}

oindent & oindent::endline (char const * finish, char const * record, signed space)

{
	oindent::print (finish, record, space);
	return (* this);
}

/*====================================================================*
 *   
 *   oindent & newline (void)
 *   oindent & newline (signed level) 
 *   oindent & newline (char const * margin, char const * indent, signed level)
 *   
 *   output the margin string followed by level offset strings;
 *   
 *--------------------------------------------------------------------*/

oindent & oindent::newline (void)

{
	oindent::print (this->mmargin, this->moffset, this->mlevel);
	return (* this);
}

oindent & oindent::newline (signed level)

{
	oindent::print (this->mmargin, this->moffset, level);
	return (* this);
}

oindent & oindent::newline (char const * margin, char const * offset, signed level)

{
	oindent::print (margin, offset, level);
	return (* this);
}

/*====================================================================*
 *
 *   oindent & print (signed level, signed space, char const *string);
 *
 *--------------------------------------------------------------------*/

oindent & oindent::print (signed level, signed space, char const * string)

{
	oindent::print (this->mmargin, this->moffset, level);
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
 *--------------------------------------------------------------------*/

oindent::oindent (void)

{
	this->mmargin = new char [1];
	this->mmargin [0] = '\0';
	this->moffset = new char [2];
	this->moffset [0] = '\t';
	this->moffset [1] = '\0';
	this->mfinish = new char [1];
	this->mfinish [0] = '\0';
	this->mrecord = new char [2];
	this->mrecord [0] = '\n';
	this->mrecord [1] = '\0';
	this->mspace = 1;
	this->mlevel = 0;
	return;
}

/*====================================================================*
 *
 *   oindent (void) 
 *
 *
 *--------------------------------------------------------------------*/

oindent::~ oindent (void)

{
	delete [] this->mmargin;
	delete [] this->moffset;
	delete [] this->mfinish;
	delete [] this->mrecord;
	return;
}

/*====================================================================*
 *   end implementation
 *--------------------------------------------------------------------*/

#endif



