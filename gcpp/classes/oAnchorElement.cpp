/*====================================================================*
 *
 *   oAnchorElement - HTML Anchor Element;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *
 *--------------------------------------------------------------------*/

#ifndef oANCHORELEMENT_SOURCE
#define oANCHORELEMENT_SOURCE

/*====================================================================*
 *   standard header files;
 *--------------------------------------------------------------------*/

#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oAnchorElement.hpp"

/*====================================================================*
 *   static data definitions; 
 *--------------------------------------------------------------------*/

char const * oAnchorElement::mscope = "";
char const * oAnchorElement::mtitle = "a";

/*====================================================================*
 *
 *   char const * ElementName () const;
 *
 *   return element name as a constant string;
 *
 *--------------------------------------------------------------------*/

char const * oAnchorElement::ElementName () const 

{
	return (oAnchorElement::mtitle);
}

/*====================================================================*
 *
 *   char const * StartTag() 
 *
 *   print element start tag with any attributes on stdout;
 *
 *--------------------------------------------------------------------*/

oAnchorElement & oAnchorElement::StartTag () 

{
	std::cout.put ('<');
	if (* this->mscope) 
	{
		std::cout << this->mscope;
		std::cout.put (':');
	}
	std::cout << this->mtitle;
	oAnchorElement::i18nAttributes.write ();
	oAnchorElement::CoreAttributes.write ();
	oAnchorElement::LinkAttributes.write ();
	std::cout.put ('>');
	return (* this);
}

/*====================================================================*
 *
 *   oAnchorElement & EmptyTag();
 *
 *   print empty element tag with any attributes on stdout;
 *
 *--------------------------------------------------------------------*/

oAnchorElement & oAnchorElement::EmptyTag () 

{
	std::cout.put ('<');
	if (* this->mscope) 
	{
		std::cout << this->mscope;
		std::cout.put (':');
	}
	std::cout << this->mtitle;
	oAnchorElement::i18nAttributes.write ();
	oAnchorElement::CoreAttributes.write ();
	oAnchorElement::LinkAttributes.write ();
	std::cout.put ('/');
	std::cout.put ('>');
	return (* this);
}

/*====================================================================*
 *
 *   oAnchorElement & EndTag();
 *
 *   print element end tag on stdout;
 *
 *--------------------------------------------------------------------*/

oAnchorElement & oAnchorElement::EndTag () 

{
	std::cout.put ('<');
	std::cout.put ('/');
	if (* this->mscope) 
	{
		std::cout << this->mscope;
		std::cout.put (':');
	}
	std::cout << this->mtitle;
	std::cout.put ('>');
	return (* this);
}

/*====================================================================*
 *
 *   oAnchorElement ();
 *   
 *   
 *--------------------------------------------------------------------*/

oAnchorElement::oAnchorElement () 

{
	return;
}

/*====================================================================*
 *
 *   ~oAnchorElement ();
 *   
 *   
 *--------------------------------------------------------------------*/

oAnchorElement::~oAnchorElement () 

{
	return;
}

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

