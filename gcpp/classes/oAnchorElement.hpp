/*====================================================================*
 *
 *   oAnchorElement.hpp - oAnchorElement class declaration;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oANCHORELEMENT_HEADER
#define oANCHORELEMENT_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "oi18nAttributes.hpp"
#include "oCoreAttributes.hpp"
#include "oLinkAttributes.hpp"

/*====================================================================*
 *   interface declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oAnchorElement 

{
public:
	oAnchorElement ();
	virtual~ oAnchorElement ();
	char const * ElementName () const;
	oi18nAttributes i18nAttributes;
	oCoreAttributes CoreAttributes;
	oLinkAttributes LinkAttributes;
	oAnchorElement & StartTag ();
	oAnchorElement & EmptyTag ();
	oAnchorElement & EndTag ();
private:
	static char const * mscope;
	static char const * mtitle;
};


/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

