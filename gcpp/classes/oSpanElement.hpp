/*====================================================================*
 *
 *   oSpanElement.hpp - declaration of oSpanElement class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oSPANELEMENT_HEADER
#define oSPANELEMENT_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/oCoreAttributes.hpp"
#include "../classes/oi18nAttributes.hpp"

/*====================================================================*
 *   interface declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oSpanElement 

{
public:
	oSpanElement ();
	virtual ~ oSpanElement ();
	char const * ElementName () const;
	oCoreAttributes CoreAttributes;
	oi18nAttributes i18nAttributes;
	oSpanElement & StartTag ();
	oSpanElement & EmptyTag ();
	oSpanElement & EndTag ();
private:
	static char const * mscope;
	static char const * mtitle;
};


/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

