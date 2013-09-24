/*====================================================================*
 *
 *   ooelement - implementation of the oelement class;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *
 *--------------------------------------------------------------------*/

#ifndef oELEMENT_SOURCE
#define oELEMENT_SOURCE

/*====================================================================*
 *   standard header files;
 *--------------------------------------------------------------------*/

#include <cstring>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oelement.hpp"

/*====================================================================*
 *
 *   char const * scope () const;
 *
 *   return element name string;
 *
 *--------------------------------------------------------------------*/

char const * oelement::scope() const

{
	return (oelement::mscope);
}

/*====================================================================*
 *
 *   char const * title () const;
 *
 *   return element name string;
 *
 *--------------------------------------------------------------------*/

char const * oelement::title() const

{
	return (oelement::mtitle);
}

/*====================================================================*
 *
 *   oelement & print () 
 *
 *   print element end tag on stdout;
 *
 *--------------------------------------------------------------------*/

oelement & oelement::print()

{
	if (* this->mscope)
	{
		std::cout << this->mscope;
		std::cout.put(':');
	}
	std::cout << this->mtitle;
	return (* this);
}

/*====================================================================*
 *
 *   oelement (char const * scope, char const * title);
 *
 *--------------------------------------------------------------------*/

oelement::oelement(char const * scope, char const * title)

{
	this->mscope = otext::save(scope);
	this->mscope = otext::save(title);
	return;
}

/*====================================================================*
 *
 *   oelement (char const * title);
 *
 *--------------------------------------------------------------------*/

oelement::oelement(char const * title)

{
	this->mscope = otext::save("");
	this->mscope = otext::save(title);
	return;
}

/*====================================================================*
 *
 *   ~oelement ();
 *
 *--------------------------------------------------------------------*/

oelement::~ oelement()

{
	return;
}

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif



