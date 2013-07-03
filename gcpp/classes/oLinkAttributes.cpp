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
	this->ReferenceAttribute = new oAttribute ("href");
	this->ReferenceLanguageAttribute = new oAttribute ("hreflang");
	this->ForwardLinkTypeAttribute = new oAttribute ("rel");
	this->ReverseLinkTypeAttribute = new oAttribute ("rev");
	this->TargetFrameAttribute = new oAttribute ("target");
	this->AccessKeyAttribute = new oAttribute ("accesskey");
	this->NavigationIndexAttribute = new oAttribute ("navindex");
	this->BaseURLAttribute = new oAttribute ("base");
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

