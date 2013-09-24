/*====================================================================*
 *
 *   oCoreAttributes.hpp - declaration of oCoreAttributes class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCOREATTRIBUTES_HEADER
#define oCOREATTRIBUTES_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/oAttribute.hpp"

/*====================================================================*
 *   class declarations;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oCoreAttributes

{
public: 
	oCoreAttributes ();
	virtual ~ oCoreAttributes ();
	oAttribute * IdentityAttribute;
	oAttribute * TitleAttribute;
	oAttribute * ClassAttribute;
	oAttribute * StyleAttribute;
	oCoreAttributes & write ();
private: 
};

/*====================================================================*
 *   end declarations;
 *--------------------------------------------------------------------*/

#endif



