/*====================================================================*
 *
 *   oinclude.hpp - declaration of oinclude class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oINCLUDE_HEADER
#define oINCLUDE_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <fstream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/types.h"     
#include "../classes/stdafx.hpp"
#include "../classes/otext.hpp"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oinclude: private otext 

{
public:
	oinclude (char const * title, char const * label);
	oinclude ();
	virtual ~ oinclude ();
	signed state () const;
	char const * title () const;
	char const * label () const;
	oinclude & state (signed state);
	oinclude & filename (char const * filename);
	oinclude & title (char const * title);
	oinclude & label (char const * label);
	oinclude & header ();
	oinclude & footer ();
private:
	char * mtitle;
	char * mclass;
	signed mstate;
};


/*====================================================================*
 *   end interface declaration;
 *--------------------------------------------------------------------*/

#endif

