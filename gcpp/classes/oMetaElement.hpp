/*====================================================================*
 *
 *   oMetaElement.hpp - declaration of oMetaElement class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oMETAELEMENT_HEADER
#define oMETAELEMENT_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/oAttribute.hpp"

/*====================================================================*
 *   interface declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oMetaElement

{
public: 
	oMetaElement ();
	virtual ~ oMetaElement ();
	char const * ElementName () const;
	oAttribute * NameAttribute;
	oAttribute * ContentTypeAttribute;
	oAttribute * SchemeAttribute;
	oAttribute * ResponseAttribute;
	oMetaElement & Contents (char const * name, char const * type);
	oMetaElement & EmptyTag (unsigned level, unsigned space);
private: 
	static char const * mscope;
	static char const * mtitle;
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif



