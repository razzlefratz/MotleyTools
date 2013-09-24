/*====================================================================*
 *
 *   oISOGlyph.hpp - declaration of oISOGlyph class.
 *
 *   this object implements conversion of ASCII characters to equivalent
 *   ISO glyph strings for display on HTML pages;
 *  
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oISOGLYPH_HEADER
#define oISOGLYPH_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec(dllexport) oISOGlyph

{
public: 
	oISOGlyph (void);
	virtual ~ oISOGlyph(void);
	char const * string(signed c);
private: 
	static char const * mtable[];
	char * mstring;
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif



