/*====================================================================*
 *
 *   othread.hpp - interface for the othread class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oTHREAD_HEADER
#define oTHREAD_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/otext.hpp"

/*====================================================================*
 *7
 *--------------------------------------------------------------------*/

class __declspec (dllexport) othread: private otext 

{
public:
	othread ();
	othread (char const * label, char const * title, char const * file);
	virtual~ othread ();
	unsigned count () const;
	bool isempty () const;
	char const * name () const;
	char const * text () const;
	char const * page () const;
	othread & name (char const * string);
	othread & text (char const * string);
	othread & page (char const * string);
	othread * above () const;
	othread * after () const;
	othread * prior () const;
	othread * below () const;
	othread * other () const;
	othread & clear ();
	othread & insert (othread * object);
	othread & append (othread * object);
	othread & remove ();
	othread & unwind ();
	othread & attach (othread * object);
	othread & detach ();
private:
	char * copy (char const * string);
	othread * mabove;
	othread * mafter;
	othread * mprior;
	othread * mbelow;
	othread * mother;
	char * mname;
	char * mtext;
	char * mpage;
};


#endif

