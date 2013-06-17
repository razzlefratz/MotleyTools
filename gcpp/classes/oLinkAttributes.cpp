/*====================================================================*
 *
 *   oLinkAttributes.cpp - definition of the oLinkAttributes class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *
 *--------------------------------------------------------------------*/

#ifndef oLINKATTRIBUTES_SOURCE
#define oLINKATTRIBUTES_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oLinkAttributes.hpp"

/*====================================================================*
 *
 *   oLinkAttributes & write ();
 *
 *
 *--------------------------------------------------------------------*/

oLinkAttributes & oLinkAttributes::write () 

{
	this->ReferenceAttribute->write ();
	this->ReferenceLanguageAttribute->write ();
	this->ForwardLinkTypeAttribute->write ();
	this->ReverseLinkTypeAttribute->write ();
	this->TargetFrameAttribute->write ();
	this->AccessKeyAttribute->write ();
	this->NavigationIndexAttribute->write ();
	this->BaseURLAttribute->write ();
	return (* this);
}


/*====================================================================*
 *
 *   oLinkAttributes ();
 *   
 *--------------------------------------------------------------------*/

oLinkAttributes::oLinkAttributes () 

{
	this->ReferenceAttribute = new oattribute ("href");
	this->ReferenceLanguageAttribute = new oattribute ("hreflang");
	this->ForwardLinkTypeAttribute = new oattribute ("rel");
	this->ReverseLinkTypeAttribute = new oattribute ("rev");
	this->TargetFrameAttribute = new oattribute ("target");
	this->AccessKeyAttribute = new oattribute ("accesskey");
	this->NavigationIndexAttribute = new oattribute ("navindex");
	this->BaseURLAttribute = new oattribute ("base");
	return;
}


/*====================================================================*
 *
 *   ~oLinkAttributes ();
 *   
 *--------------------------------------------------------------------*/

oLinkAttributes::~oLinkAttributes () 

{
	return;
}


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

