/*====================================================================*
 *
 *   oCoreAttributes.cpp - implementation of oCoreAttributes class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *
 *--------------------------------------------------------------------*/

#ifndef oCOREATTRIBUTES_SOURCE
#define oCOREATTRIBUTES_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oCoreAttributes.hpp"

/*====================================================================*
 *
 *   oCoreAttributes & write ();
 *
 *--------------------------------------------------------------------*/

oCoreAttributes & oCoreAttributes::write ()

{
	this->IdentityAttribute->write ();
	this->TitleAttribute->write ();
	this->ClassAttribute->write ();
	this->StyleAttribute->write ();
	return (* this);
}

/*====================================================================*
 *
 *   oCoreAttributes ();
 *   
 *--------------------------------------------------------------------*/

oCoreAttributes::oCoreAttributes ()

{
	this->IdentityAttribute = new oAttribute ("id");
	this->TitleAttribute = new oAttribute ("title");
	this->ClassAttribute = new oAttribute ("class");
	this->StyleAttribute = new oAttribute ("style");
	return;
}

/*====================================================================*
 *
 *   ~oCoreAttributes ();
 *   
 *   
 *--------------------------------------------------------------------*/

oCoreAttributes::~ oCoreAttributes ()

{
	return;
}

/*====================================================================*
 *   end definition
 *--------------------------------------------------------------------*/

#endif



