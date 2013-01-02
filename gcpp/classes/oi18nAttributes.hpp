/*====================================================================*
 *
 *   oi18nAttributes.hpp - declaration of oi18nAttributes class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oI18NATTRIBUTES_HEADER
#define oI18NATTRIBUTES_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/oattribute.hpp"
#include "../classes/otext.hpp"

/*====================================================================*
 *   class declarations;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oi18nAttributes: private otext 

{
public:
	oi18nAttributes ();
	virtual ~ oi18nAttributes ();
	oattribute * LanguageAttribute;
	oattribute * DirectionAttribute;
	oi18nAttributes & write ();
private:
};


/*====================================================================*
 *   end declarations;
 *--------------------------------------------------------------------*/

#endif

