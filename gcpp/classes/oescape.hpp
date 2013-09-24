/*====================================================================*
 *
 *   oescape.hpp - interface for the oescape class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oESCAPE_HEADER
#define oESCAPE_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/oascii.hpp"

/*====================================================================*
 *   constants;
 *--------------------------------------------------------------------*/

#define oESCAPE_NOTABLE 1
#define oESCAPE_ISO_646_1983 1

/*====================================================================*
 *   declarations;
 *--------------------------------------------------------------------*/

class __declspec(dllexport) oescape: private oascii

{
public: 
	oescape ();
	virtual ~ oescape();
	static unsigned define(signed c, signed e);
	static unsigned unescape(signed c);
	static char * unescape(char * string);
private: 
	static unsigned char mtable[];
};

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif



