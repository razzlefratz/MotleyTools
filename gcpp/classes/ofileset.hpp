/*====================================================================*
 *
 *   ofileset.hpp - interface for the ofileset class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oFILESET_HEADER
#define oFILESET_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/ocontext.hpp"
#include "../classes/otext.hpp"

/*====================================================================*
 *7
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ofileset: private otext 

{
public:
	ofileset ();
	ofileset (char const *pathname);
	virtual ~ ofileset ();
	char const *fullpath (bool increment);
	char const *fullname () const;
	char const *pathname () const;
	char const *filename () const;
	char const *basename () const;
	char const *extender () const;
	ofileset & makepath ();
	ofileset & filespec (char const *filespec);
	ofileset & pathname (char const *filespec);
	ofileset & filename (char const *filespec);
	ofileset & basename (char const *filespec);
	ofileset & extender (char const *filespec);
	unsigned int index () const;
	unsigned int field () const;
	ofileset & index (unsigned int index);
	ofileset & field (unsigned int field);
private:
	ocontext *mcontext;
	char *mfullname;
	char *mpathname;
	char *mbasename;
	char *mfilename;
	char *mextender;
	unsigned mindex;
	unsigned mfield;
};


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

