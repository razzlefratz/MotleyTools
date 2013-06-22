/*====================================================================*
 *
 *   oLinkAttributes.hpp - declaration of oLinkAttributes class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oLINKATTRIBUTES_HEADER
#define oLINKATTRIBUTES_HEADER

/*====================================================================*
 *   custom header files;   
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/oAttribute.hpp"

/*====================================================================*
 *   class declarations;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oLinkAttributes 

{
public:
	oLinkAttributes ();
	virtual~ oLinkAttributes ();
	oAttribute * ReferenceAttribute;
	oAttribute * ReferenceLanguageAttribute;
	oAttribute * ForwardLinkTypeAttribute;
	oAttribute * ReverseLinkTypeAttribute;
	oAttribute * TargetFrameAttribute;
	oAttribute * AccessKeyAttribute;
	oAttribute * NavigationIndexAttribute;
	oAttribute * BaseURLAttribute;
	oLinkAttributes & write ();
private:
	
};


/*====================================================================*
 *   end declarations;
 *--------------------------------------------------------------------*/

#endif

