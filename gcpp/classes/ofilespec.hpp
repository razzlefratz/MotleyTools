/*====================================================================*
 *
 *   ofilespec.hpp - interface for the ofilespec class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oFILESPEC_HEADER
#define oFILESPEC_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <sys/stat.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/ocontext.hpp"

/*====================================================================*
 *7
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ofilespec: private ocontext 

{
public:
	ofilespec ();
	ofilespec (char const * fullname);
	virtual~ ofilespec ();
	char const * fullpath ();
	char const * fullname () const;
	char const * pathname () const;
	char const * filename () const;
	char const * basename () const;
	char const * extender () const;
	char const * longname () const;
	char const * tempname (char const * filename);
	char const * likename (char const * extender);
	char const * savename (char const * extender);
	char const * savename (unsigned number, unsigned length);
	ofilespec & makepath ();
	ofilespec & operator = (char const * filespec);
	ofilespec & filespec (char const * filespec);
	ofilespec & pathname (char const * filespec);
	ofilespec & filename (char const * filespec);
	ofilespec & basename (char const * filespec);
	ofilespec & extender (char const * filespec);
	ofilespec & peek ();
protected:
	private: static ofilespec scratch;
	char * mfullname;
	char * mpathname;
	char * mfilename;
	char * mbasename;
	char * mextender;
};


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

