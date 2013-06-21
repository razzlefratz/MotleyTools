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
#include "../classes/oattribute.hpp"

/*====================================================================*
 *   class declarations;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oLinkAttributes 

{
public:
	oLinkAttributes ();
	virtual~ oLinkAttributes ();
	oattribute * ReferenceAttribute;
	oattribute * ReferenceLanguageAttribute;
	oattribute * ForwardLinkTypeAttribute;
	oattribute * ReverseLinkTypeAttribute;
	oattribute * TargetFrameAttribute;
	oattribute * AccessKeyAttribute;
	oattribute * NavigationIndexAttribute;
	oattribute * BaseURLAttribute;
	oLinkAttributes & write ();
private:
	
};


/*====================================================================*
 *   end declarations;
 *--------------------------------------------------------------------*/

#endif

