/*====================================================================*
 *
 *   oMetaElement - HTML SPAN object; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *
 *--------------------------------------------------------------------*/

#ifndef oMETAELEMENT_SOURCE
#define oMETAELEMENT_SOURCE

/*====================================================================*
 *   standard header files;
 *--------------------------------------------------------------------*/

#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oMetaElement.hpp"

/*====================================================================*
 *   static data initialization;
 *--------------------------------------------------------------------*/

char const * oMetaElement::mscope = "";
char const * oMetaElement::mtitle = "meta";

/*====================================================================*
 *
 *   char const * ElementName () const;
 *
 *   return the html element name as a string constant;
 *
 *--------------------------------------------------------------------*/

char const * oMetaElement::ElementName () const

{
	return (oMetaElement::mtitle);
}

/*====================================================================*
 *
 *   oMetaElement & Contents (char const * name, char const * type);
 *
 *   return an empty html tag; this is the start tag with internal slash
 *   to indicate an empty block of text; 
 *
 *--------------------------------------------------------------------*/

oMetaElement & oMetaElement::Contents (char const * name, char const * type)

{
	this->NameAttribute->value (name);
	this->ContentTypeAttribute->value (type);
	return (* this);
}

/*====================================================================*
 *
 *   char const *EmptyTag();
 *
 *   return an empty html tag; this is the start tag with internal slash
 *   to indicate an empty block of text; 
 *
 *--------------------------------------------------------------------*/

oMetaElement & oMetaElement::EmptyTag (unsigned level, unsigned space)

{
	while (level--)
	{
		std::cout.put ('\t');
	}
	std::cout.put ('<');
	std::cout << oMetaElement::mtitle;
	this->NameAttribute->write ();
	this->ContentTypeAttribute->write ();
	this->SchemeAttribute->write ();
	this->ResponseAttribute->write ();
	std::cout.put ('/');
	std::cout.put ('>');
	while (space--)
	{
		std::cout.put ('\n');
	}
	return (* this);
}

/*====================================================================*
 *
 *   oMetaElement ();
 *   
 *--------------------------------------------------------------------*/

oMetaElement::oMetaElement ()

{
	this->NameAttribute = new oAttribute ("name", "content-type");
	this->ContentTypeAttribute = new oAttribute ("content", "text/html;iso-8895-1");
	this->SchemeAttribute = new oAttribute ("scheme");
	this->ResponseAttribute = new oAttribute ("http-equiv");
	return;
}

/*====================================================================*
 *
 *   ~oMetaElement ();
 *   
 *--------------------------------------------------------------------*/

oMetaElement::~ oMetaElement ()

{
	return;
}

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif



