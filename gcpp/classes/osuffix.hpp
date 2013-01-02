/*====================================================================*
 *
 *   osuffix.hpp - interface for the osuffix class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oSUFFIX_HEADER
#define oSUFFIX_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *7
 *--------------------------------------------------------------------*/

class __declspec (dllexport) osuffix 

{
public:
	osuffix ();
	virtual ~ osuffix ();
	void define (char const *symbol, char const *string);
	char const *lookup (char const *symbol);
private:
	char m_char;
	char *m_text;
	osuffix *m_prior;
	osuffix *m_after;
	osuffix *m_equal;
};


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

