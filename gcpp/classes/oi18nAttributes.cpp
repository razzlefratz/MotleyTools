/*====================================================================*
 *
 *   oi18nAttributes.cpp - implementation of oi18nAttributes class;
 *
 *   this object implements the w3c i18n core markup attributes; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *
 *--------------------------------------------------------------------*/

#ifndef oI18NATTRIBUTES_SOURCE
#define oI18NATTRIBUTES_SOURCE

/*====================================================================*
 *   standard header files;
 *--------------------------------------------------------------------*/

#include <cstring>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oi18nAttributes.hpp"

/*====================================================================*
 *
 *   oi18nAttributes & oi18nAttributes::write ();
 *
 *--------------------------------------------------------------------*/

oi18nAttributes & oi18nAttributes::write ()

{
	this->LanguageAttribute->write ();
	this->DirectionAttribute->write ();
	return (* this);
}

/*====================================================================*
 *
 *   oi18nAttributes ();
 *   
 *--------------------------------------------------------------------*/

oi18nAttributes::oi18nAttributes ()

{
	this->LanguageAttribute = new oAttribute ("lang");
	this->DirectionAttribute = new oAttribute ("dir");
	return;
}

/*====================================================================*
 *
 *   ~oi18nAttributes ();
 *   
 *--------------------------------------------------------------------*/

oi18nAttributes::~ oi18nAttributes ()

{
	return;
}

/*====================================================================*
 *   end definition
 *--------------------------------------------------------------------*/

#endif



