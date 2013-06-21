/*====================================================================*
 *
 *   oMACAddress.hpp - interface for the oMACAddress class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oMACADDRESS_HEADER
#define oMACADDRESS_HEADER

#include "../classes/stdafx.hpp"
#include "../classes/types.h"

/*====================================================================*
 *   class constants;
 *--------------------------------------------------------------------*/

#define oMACADDRESS_EXTENDER ':'
#define oMACADDRESS_TOOSHORT 1
#define oMACADDRESS_TOOLONG  2
#define oMACADDRESS_ILLEGAL  3
#define oMACADDRESS_OCTET 6

/*====================================================================*
 * 
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oMACAddress 

{
public:
	oMACAddress ();
	virtual~ oMACAddress ();
	const unsigned char * number () const;
	char const * string () const;
	errno_t error () const;
	oMACAddress & spec (char const * string);
	oMACAddress & encode (char const * string);
	oMACAddress & decode (const unsigned char []);
private:
	static char const digit [];
	unsigned char * mnumber;
	char * mstring;
	errno_t merror;
};


/*====================================================================*
 *   end interface declaration;
 *--------------------------------------------------------------------*/

#endif

