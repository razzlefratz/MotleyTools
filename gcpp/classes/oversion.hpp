/*====================================================================*
 *
 *   oversion.hpp - declarations of the oversion class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oVERSION_HEADER
#define oVERSION_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/otext.hpp"

/*====================================================================*
 *  class constants;
 *--------------------------------------------------------------------*/

#define PROGRAM "untitled"
#define COMPANY "Charles Maier"
#define PROJECT "Motley Toolkit"
#define PACKAGE "motley-tools"
#define VERSION "1.9.4"
#define RELEASE __TIME__ " " __DATE__
#define CONTACT "cmaier@cmassoc.net"
#define LICENSE "ISC License"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oversion: private otext

{
public: 
	oversion ();
	virtual ~ oversion ();
	char const * program () const;
	char const * company () const;
	char const * project () const;
	char const * package () const;
	char const * version () const;
	char const * release () const;
	char const * license () const;
	char const * contact () const;
	oversion & program (char const *);
	oversion & company (char const *);
	oversion & project (char const *);
	oversion & package (char const *);
	oversion & version (char const *);
	oversion & release (char const *);
	oversion & license (char const *);
	oversion & contact (char const *);
	oversion & print ();
private: 
	char * mprogram;
	char * mcompany;
	char * mproject;
	char * mpackage;
	char * mversion;
	char * mrelease;
	char * mlicense;
	char * mcontact;
};

/*====================================================================*
 *   end class declaration;
 *--------------------------------------------------------------------*/

#endif



