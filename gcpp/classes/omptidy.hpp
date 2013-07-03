/*====================================================================*
 *
 *   omptidy.hpp - class declaration for omptidy class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oMPTIDY_HEADER
#define oMPTIDY_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/osource.hpp"
#include "../classes/oascii.hpp"
#include "../classes/otext.hpp"

/*====================================================================*
 *   class constants;
 *--------------------------------------------------------------------*/

#define oMPTIDY_SYMBOLSIZE 4096
#define oMPTIDY_S_PROJECT "project"
#define oMPTIDY_S_PROGRAM "program"
#define oMPTIDY_S_PACKAGE "package"
#define oMPTIDY_S_RELEASE "release"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) omptidy: private otext, private oascii, private osource 

{
public:
	omptidy (void);
	virtual ~ omptidy (void);
	char const * project (void) const;
	char const * program (void) const;
	char const * package (void) const;
	char const * release (void) const;
	omptidy & project (char const *);
	omptidy & program (char const *);
	omptidy & package (char const *);
	omptidy & release (char const *);
	omptidy & filename (char const *);
	signed tidy (signed c);
private:
	char * mproject;
	char * mprogram;
	char * mpackage;
	char * mrelease;
	char * mstring;
};

#endif

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

