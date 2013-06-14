/*====================================================================*
 *
 *   oPageLinkElement - HTML ANCHOR object; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *
 *--------------------------------------------------------------------*/

#ifndef oPAGELINKELEMENT_SOURCE
#define oPAGELINKELEMENT_SOURCE

/*====================================================================*
 *   standard header files;
 *--------------------------------------------------------------------*/

#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oPageLinkElement.hpp"

/*====================================================================*
 *
 *   char const * name () const;
 *
 *--------------------------------------------------------------------*/

char const * oPageLinkElement::name () const 

{
	return (this->mname);
}


/*====================================================================*
 *
 *   oPageLinkElement & name (char const * string);
 *
 *--------------------------------------------------------------------*/

oPageLinkElement & oPageLinkElement::name (char const * string) 

{
	this->mname = otext::replace (this->mname, string);
	return (* this);
}


/*====================================================================*
 *
 *   oPageLinkeElement & link (char const * text, char const * path);
 *
 *
 *--------------------------------------------------------------------*/

oPageLinkElement & oPageLinkElement::link (char const * text, char const * path) 

{
	AnchorElement.CoreAttributes.TitleAttribute->value (text);
	AnchorElement.LinkAttributes.ReferenceAttribute->value (path);
	return (* this);
}


/*====================================================================*
 *
 *   char const * write () 
 *
 *   format a page link element and return a pointer to it; page links are
 *   merely anchor elements enclosed in brackets ('[',']');
 *
 *--------------------------------------------------------------------*/

oPageLinkElement & oPageLinkElement::write () 

{
	std::cout.put ('[');
	this->AnchorElement.StartTag ();
	std::cout << this->mname;
	this->AnchorElement.EndTag ();
	std::cout.put (']');
	return (* this);
}


/*====================================================================*
 *
 *   oPageLinkElement (char const *string);
 *   
 *   
 *--------------------------------------------------------------------*/

oPageLinkElement::oPageLinkElement (char const * name) 

{
	this->mname = otext::save (name);
	return;
}


/*====================================================================*
 *
 *   oPageLinkElement ();
 *   
 *   
 *--------------------------------------------------------------------*/

oPageLinkElement::oPageLinkElement () 

{
	this->mname = otext::save ("LINK");
	return;
}


/*====================================================================*
 *
 *   ~oPageLinkElement ();
 *   
 *   
 *--------------------------------------------------------------------*/

oPageLinkElement::~oPageLinkElement () 

{
	delete [] this->mname;
	return;
}


/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

