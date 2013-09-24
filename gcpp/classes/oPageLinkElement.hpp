/*====================================================================*
 *
 *   oPageLinkElement.hpp - declaration of oPageLinkElement class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oPAGELINKELEMENT_HEADER
#define oPAGELINKELEMENT_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/oAnchorElement.hpp"
#include "../classes/otext.hpp"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oPageLinkElement: private otext

{
public: 
	oPageLinkElement ();
	oPageLinkElement (char const * string);
	virtual ~ oPageLinkElement ();
	char const * name () const;
	oPageLinkElement & name (char const * string);
	oPageLinkElement & link (char const * text, char const * path);
	oAnchorElement AnchorElement;
	oPageLinkElement & write ();
private: 
	char * mname;
};

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif



