/*====================================================================*
 *
 *   oAttribute.cpp - implementation of oAttribute class;
 *
 *   this class implements HTML-style attributes where an attribute
 *   a label/value pair; by convention, an attribute starts with a
 *   space followed by a label, an equal sign and a value; the value
 *   is often enclosed in quotes;
 *
 *   ... href="http://www.cmassoc.net" title="Hello World" ...
 *
 *   there are other variations, however; some are shown below;
 *
 *   ...$abc:timeofday $def:123-456-798 ...
 *
 *   in this example, the space is replace by a dollar, the equals
 *   by a colon, the quotes are omitted and a semicolon follows;
 *
 *   ..., abc=def, ghi=123, ...
 *
 *   there std::endless variations on this format;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oATTRIBUTE_SOURCE
#define oATTRIBUTE_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oAttribute.hpp"

/*====================================================================*
 *   class variables;
 *--------------------------------------------------------------------*/

char const * oAttribute::mspace = " ";
char const * oAttribute::mequal = "=";
char const * oAttribute::mquote = "\'";
char const * oAttribute::mcomma = "";

/*====================================================================*
 *
 *   char const * label () const;
 *
 *   return the attribute label (name) string as a constant;
 *
 *--------------------------------------------------------------------*/

char const * oAttribute::label () const

{
	return (this->mlabel);
}

/*====================================================================*
 *
 *   char const * value () const;
 *
 *   return the attribute value (value) string as a constant;
 *
 *--------------------------------------------------------------------*/

char const * oAttribute::value () const

{
	return (this->mvalue);
}

/*====================================================================*
 *
 *   oAttribute & value (char const * string);
 *
 *   replace the attribute value (value) string;
 *
 *--------------------------------------------------------------------*/

oAttribute & oAttribute::value (char const * string)

{
	this->mvalue = otext::replace (this->mvalue, string);
	return (* this);
}

/*====================================================================*
 *
 *   oAttribute & value (unsigned number);
 *
 *   replace the attribute value (value) string with an integer; the
 *   string length is determined by integer magnitude and will only
 *   be as long as needed;
 *
 *--------------------------------------------------------------------*/

oAttribute & oAttribute::value (unsigned number)

{
	char string [32];
	char * sp = string + sizeof (string);
	* -- sp = (char) (0);
	do 
	{
		* -- sp = '0' + number % 10;
		number /=  10;
	}
	while ((sp > string) && (number));
	this->mvalue = otext::replace (this->mvalue, sp);
	return (* this);
}

/*====================================================================*
 *
 *   oAttribute & value (unsigned number, unsigned digits)
 *
 *   replace the attribute value (value) string with an integer; the
 *   string length is fixed and will be padded/truncated as needed;
 *
 *--------------------------------------------------------------------*/

oAttribute & oAttribute::value (unsigned number, unsigned digits)

{
	char string [digits + 1];
	char * sp = string + sizeof (string);
	* -- sp = (char) (0);
	do 
	{
		* -- sp = '0' + number % 10;
		number /=  10;
	}
	while ((sp > string) || (number));
	this->mvalue = otext::replace (this->mvalue, sp);
	return (* this);
}

/*====================================================================*
 *
 *   oAttribute & write ();
 *
 *   <space><label><equal><quote><value><quote><comma>
 *
 *--------------------------------------------------------------------*/

oAttribute & oAttribute::write ()

{
	if (* this->mvalue)
	{
		std::cout << oAttribute::mspace;
		if (* this->mlabel)
		{
			std::cout << this->mlabel << oAttribute::mequal;
		}
		std::cout << oAttribute::mquote << this->mvalue << oAttribute::mquote;
		std::cout << oAttribute::mcomma;
	}
	return (* this);
}

/*====================================================================*
 *
 *   oAttribute (char const * label, char const * value);
 *
 *--------------------------------------------------------------------*/

oAttribute::oAttribute (char const * label, char const * value)

{
	this->mlabel = otext::save (label);
	this->mvalue = otext::save (value);
	return;
}

/*====================================================================*
 *
 *   oAttribute (char const * label);
 *
 *--------------------------------------------------------------------*/

oAttribute::oAttribute (char const * label)

{
	this->mlabel = otext::save (label);
	this->mvalue = otext::save ("");
	return;
}

/*====================================================================*
 *
 *   ~oAttribute ();
 *
 *
 *--------------------------------------------------------------------*/

oAttribute::~ oAttribute ()

{
	delete [] this->mlabel;
	delete [] this->mvalue;
	return;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif



