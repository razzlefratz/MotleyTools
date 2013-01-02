/*====================================================================*
 *
 *   opackage.hpp - interface for the opackage class.
 *
 *   parse GNU/Linux style archive specifications and expose package, release
 *   and trailer components;
 *
 *   a GNU/Linux syle archive specifictions has the following form:
 *
 *   <pathname>/<package>-<release>.<trailer>
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oPACKAGE_HEADER
#define oPACKAGE_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#define oPACKAGE_EXTENDERS_MAX 100

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

class __declspec (dllexport) opackage 

{
public:
	opackage ();
	opackage (char const *filespec);
	virtual ~ opackage ();
	char const *archive () const;
	char const *package () const;
	char const *product () const;
	char const *release () const;
	char const *trailer () const;
	opackage & operator= (char const *filespec);
	opackage & filespec (char const *filespec);
	opackage & extender (char const *extender);
	opackage & peek ();
protected:
private:
	static char const *extenders [];
	static char *extract (char string [], char const *start, char const *limit);
	char *marchive;
	char *mpackage;
	char *mproduct;
	char *mrelease;
	char *mtrailer;
};


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

