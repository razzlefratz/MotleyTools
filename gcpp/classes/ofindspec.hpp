/*====================================================================*
 *
 *   ofindspec.hpp - interface for the ofindspec class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oFINDSPEC_HEADER
#define oFINDSPEC_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/oerror.hpp"
#include "../classes/opathspec.hpp"

/*====================================================================*
 *7
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ofindspec: private oerror 

{
public:
	ofindspec ();
	ofindspec (char const * fullname);
	virtual ~ ofindspec ();
	char const * fullname ();
	char const * pathname () const;
	char const * filename () const;
	char const * longname () const;
	char const * basename () const;
	char const * extender () const;
	ofindspec & fullname (char const * filespec);
	ofindspec & pathname (char const * filespec);
	ofindspec & filename (char const * filespec);
	ofindspec & basename (char const * filespec);
	ofindspec & extender (char const * filespec);
	char const * altfilename (char const * extender);
	char const * altextender (char const * extender);
	char const * addextender (char const * extender);
	char const * serial (unsigned number, unsigned length);
	ofindspec & peek ();
private:
	opathspec pathspec;
	unsigned mfindmode;
	char * mtempname;
	char * mpathname;
	char * mfilename;
	char * mwildcard;
	char * mbasename;
	char * mextender;
};

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

