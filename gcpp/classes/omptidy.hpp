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
#include "../classes/otext.hpp"
#include "../classes/ocollect.hpp"
#include "../classes/oascii.hpp"

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

class __declspec (dllexport) omptidy: private otext, private ocollect, private oascii 

{
public:
	omptidy ();
	virtual ~ omptidy ();
	char const * project () const;
	char const * program () const;
	char const * package () const;
	char const * release () const;
	omptidy & project (char const * project);
	omptidy & program (char const * program);
	omptidy & package (char const * package);
	omptidy & release (char const * release);
	omptidy & page ();
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

