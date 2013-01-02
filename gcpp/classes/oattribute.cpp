/*====================================================================*
 *
 *   oattribute.cpp - implementation of oattribute class;
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
 *   there endless variations on this format;
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

#include "../classes/oattribute.hpp"

/*====================================================================*
 *   class variables;
 *--------------------------------------------------------------------*/

char const * oattribute::mspace = " ";
char const * oattribute::mequal = "=";
char const * oattribute::mquote = "\'";
char const * oattribute::mcomma = "";

/*====================================================================*
 *
 *   char const * label () const;
 *
 *   return the attribute label (name) string as a constant;
 *
 *--------------------------------------------------------------------*/

char const *oattribute::label () const 

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

char const *oattribute::value () const 

{
	return (this->mvalue);
}


/*====================================================================*
 *
 *   oattribute & value (char const * string);
 *
 *   replace the attribute value (value) string;
 *
 *--------------------------------------------------------------------*/

oattribute & oattribute::value (char const * string) 

{
	this->mvalue = otext::replace (this->mvalue, string);
	return (*this);
}


/*====================================================================*
 *
 *   oattribute & value (unsigned number);
 *
 *   replace the attribute value (value) string with an integer; the
 *   string length is determined by integer magnitude and will only
 *   be as long as needed;
 *
 *--------------------------------------------------------------------*/

oattribute & oattribute::value (unsigned number) 

{
	unsigned digits = 32;
	char string [digits+1];
	string [digits] = (char)(0);
	do 
	{
		string [--digits] = number % 10;
		number /= 10;
	}
	while (number);
	this->mvalue = otext::replace (this->mvalue, &string [digits]);
	return (*this);
}


/*====================================================================*
 *
 *   oattribute & value (unsigned number, unsigned digits) 
 *
 *   replace the attribute value (value) string with an integer; the
 *   string length is fixed and will be padded/truncated as needed;
 *
 *--------------------------------------------------------------------*/

oattribute & oattribute::value (unsigned number, unsigned digits) 

{
	char string [digits+1];
	string [digits] = (char)(0);
	while (digits) 
	{
		string [--digits] = number % 10;
		number /= 10;
	}
	this->mvalue = otext::replace (this->mvalue, string);
	return (*this);
}


/*====================================================================*
 *
 *   oattribute & write ();
 *
 *   <space><label><equal><quote><value><quote><comma>
 *
 *--------------------------------------------------------------------*/

oattribute & oattribute::write () 

{
	if (*this->mvalue) 
	{
		std::cout << oattribute::mspace;
		if (*this->mlabel) 
		{
			std::cout << this->mlabel << oattribute::mequal;
		}
		std::cout << oattribute::mquote << this->mvalue << oattribute::mquote;
		std::cout << oattribute::mcomma;
	}
	return (*this);
}


/*====================================================================*
 *
 *   oattribute (char const * label, char const * value);
 *   
 *--------------------------------------------------------------------*/

oattribute::oattribute (char const * label, char const * value) 

{
	this->mlabel = otext::save (label);
	this->mvalue = otext::save (value);
	return;
}


/*====================================================================*
 *
 *   oattribute (char const * label);
 *   
 *--------------------------------------------------------------------*/

oattribute::oattribute (char const * label) 

{
	this->mlabel = otext::save (label);
	this->mvalue = otext::save ("");
	return;
}


/*====================================================================*
 *
 *   ~oattribute ();
 *   
 *   
 *--------------------------------------------------------------------*/

oattribute::~oattribute () 

{
	delete [] this->mlabel;
	delete [] this->mvalue;
	return;
}


/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

