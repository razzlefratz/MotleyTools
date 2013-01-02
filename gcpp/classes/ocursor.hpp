/*====================================================================*
 *
 *   ocursor.hpp - interface for the ocursor class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCURSOR_HEADER
#define oCURSOR_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstddef>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ocursor 

{
public:
	ocursor ();
	virtual ~ ocursor ();
	ocursor & clear ();
	ocursor & count (char c);
	size_t charcount () const;
	size_t pagecount () const;
	size_t linecount () const;
	size_t rowcount () const;
	size_t colcount () const;
private:
	size_t mchar;
	size_t mline;
	size_t mpage;
	size_t mrow;
	size_t mcol;
};


/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#endif

