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

#include "../classes/stdafx.hpp"
#include "../classes/otext.hpp"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oinclude: private otext

{
public: 
	virtual ~ oinclude (void);
	oinclude (char const * title, char const * label);
	oinclude (void);
	signed state (void) const;
	char const * title (void) const;
	char const * label (void) const;
	oinclude & state (signed state);
	oinclude & filename (char const * filename);
	oinclude & title (char const * title);
	oinclude & label (char const * label);
	oinclude & header (void);
	oinclude & footer (void);
private: 
	char * mtitle;
	char * mclass;
	signed mstate;
};

/*====================================================================*
 *   end interface declaration;
 *--------------------------------------------------------------------*/

#endif



