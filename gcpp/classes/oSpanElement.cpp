/*====================================================================*
 *
 *   oSpanElement - HTML SPAN object;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *
 *--------------------------------------------------------------------*/

#ifndef oSPANELEMENT_SOURCE
#define oSPANELEMENT_SOURCE

/*====================================================================*
 *   standard header files;
 *--------------------------------------------------------------------*/

#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oSpanElement.hpp"

/*====================================================================*
 *   static data initialization;
 *--------------------------------------------------------------------*/

char const * oSpanElement::mscope = "";
char const * oSpanElement::mtitle = "span";

/*====================================================================*
 *
 *   char const * ElementName () const;
 *
 *   return element name string;
 *
 *--------------------------------------------------------------------*/

char const * oSpanElement::ElementName () const

{
	return (oSpanElement::mtitle);
}

/*====================================================================*
 *
 *   oSpanElement & StartTag ()
 *
 *   print element start tag on stdout;
 *
 *--------------------------------------------------------------------*/

oSpanElement & oSpanElement::StartTag ()

{
	std::cout.put ('<');
	if (* this->mscope)
	{
		std::cout << this->mscope;
		std::cout.put (':');
	}
	std::cout << this->mtitle;
	oSpanElement::i18nAttributes.write ();
	oSpanElement::CoreAttributes.write ();
	std::cout.put ('>');
	return (* this);
}

/*====================================================================*
 *
 *   oSpanElement & EmptyTag ()
 *
 *   print element empty tag on stdout;
 *
 *--------------------------------------------------------------------*/

oSpanElement & oSpanElement::EmptyTag ()

{
	std::cout.put ('<');
	if (* this->mscope)
	{
		std::cout << this->mscope;
		std::cout.put (':');
	}
	std::cout << this->mtitle;
	oSpanElement::i18nAttributes.write ();
	oSpanElement::CoreAttributes.write ();
	std::cout.put ('/');
	std::cout.put ('>');
	return (* this);
}

/*====================================================================*
 *
 *   oSpanElement & EndTag ()
 *
 *   print element end tag on stdout;
 *
 *--------------------------------------------------------------------*/

oSpanElement & oSpanElement::EndTag ()

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
 *   oSpanElement ();
 *
 *--------------------------------------------------------------------*/

oSpanElement::oSpanElement ()

{
	return;
}

/*====================================================================*
 *
 *   ~oSpanElement ();
 *
 *--------------------------------------------------------------------*/

oSpanElement::~ oSpanElement ()

{
	return;
}

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif



